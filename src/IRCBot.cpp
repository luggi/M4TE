#include <iostream>
#include <algorithm>
#include <string.h>

#ifndef USE_SFML_SOCKETS
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include "IRCBot.h"
#include "log.h"

// http://stackoverflow.com/questions/236129/split-a-string-in-c
template < class ContainerT >
void tokenize(const std::string& str, ContainerT& tokens,
              const std::string& delimiters = " ", bool trimEmpty = false)
{
   std::string::size_type pos, lastPos = 0;

   using value_type = typename ContainerT::value_type;
   using size_type  = typename ContainerT::size_type;

   while (true) {
      pos = str.find_first_of(delimiters, lastPos);
      if (pos == std::string::npos) {
         pos = str.length();

         if (pos != lastPos || !trimEmpty) {
            tokens.push_back(value_type(str.data()+lastPos,
                  (size_type)pos-lastPos ));
        }

         break;
      } else {
         if (pos != lastPos || !trimEmpty) {
            tokens.push_back(value_type(str.data()+lastPos,
                  (size_type)pos-lastPos ));
        }
      }

      lastPos = pos + 1;
   }
}

IRCBot::IRCBot(const std::string &config_filename) : my_connected(false), my_notice_received(false), my_motd_received(false)
{
    my_config_manager.load(config_filename);
}

bool IRCBot::connect()
{
    const std::string &ip_address = my_config_manager.getServer();
    const unsigned short int &port = my_config_manager.getServerport();

#ifdef USE_SFML_SOCKETS
    sf::Socket::Status status = my_socket.connect(ip_address, port);
    if (sf::Socket::Done != status) {
        my_connected = false;
        return false;
    }
#else
    struct sockaddr_in server_addr;
    struct hostent *server;

    my_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sockfd < 0) {
        my_connected = false;
        return false;
    }

    server = gethostbyname(ip_address.c_str());
    if (NULL == server) {
        LOG_ERROR("gethostbyname returned NULL for " + ip_address);
        my_connected = false;
        return false;
    }

    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char*)&server_addr.sin_addr.s_addr,
        server->h_length);
    server_addr.sin_port = htons(port);

    if (::connect(my_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        LOG_ERROR(strerror(errno));
        my_connected = false;
        return false;
    }
#endif

    my_connected = true;

    return true;
}

bool IRCBot::login()
{
    const std::string &nick = my_config_manager.getUsername();

    if (!send_message("NICK " + nick)) {
        return false;
    }

    // http://stackoverflow.com/questions/5199808/irc-user-message-makes-no-sense-to-me
    if (!send_message("USER " + nick + " localhost * :" + nick)) {
        return false;
    }

    return true;
}

bool IRCBot::process()
{
    std::string line;

    if (!read_until(IRC_LINE_DELIMITERS, line)) {
        disconnect();
        return false;
    }

    process_input_line(line);

    return true;
}

void IRCBot::disconnect()
{
#ifdef USE_SFML_SOCKETS
    my_socket.disconnect();
#else
    close(my_sockfd);
#endif
    my_connected = false;
}

bool IRCBot::connected()
{
    return my_connected;
}

void IRCBot::join_channels()
{
    std::vector<std::string> channels = my_config_manager.getChannels();
    for (auto &channel : channels) {
        send_message("JOIN " + channel);
    }
}

void IRCBot::wait_for_notice()
{
    while (process()) {
        if (my_notice_received)
            return;
    }
}

void IRCBot::wait_for_motd()
{
    while (process()) {
        if (my_motd_received)
            return;
    }
}

void IRCBot::process_input_line(const std::string &line)
{
    LOG_INFO("RECEIVED: " + line);

    std::vector<std::string> tokens;

    tokenize(line, tokens, "\t ");

    if ("PING" == tokens[0])
        send_message("PONG " + tokens[1]);

    if ("376" == tokens[1])
        my_motd_received = true;

    if ("NOTICE" == tokens[1])
        my_notice_received = true;
}

bool IRCBot::read_until(const std::string &delimiters, std::string &line)
{
    bool error = false;

    auto beg = my_network_buffer.begin();

    while (!error) {
        auto pos = std::search(beg, my_network_buffer.end(),
                               delimiters.begin(), delimiters.end());

        if (pos != my_network_buffer.end()) {
            // delimiters found, return with data
            line = std::string(my_network_buffer.begin(), pos); /* ignore delimiters */
            my_network_buffer.erase(my_network_buffer.begin(),pos+delimiters.length());
            return true;
        } else {
            // need to get more data
            char buf[1024];
            std::size_t received_count;

            // store distance, to later determine where to search from
            // (we don't want the whole buffer to be searched again
            // because we can skip stuff that has already been searched
            // through)
            auto dist = std::distance(my_network_buffer.begin(), my_network_buffer.end());

#ifdef USE_SFML_SOCKETS
            if (my_socket.receive(buf, sizeof(buf), received_count) != sf::Socket::Done) {
                LOG_ERROR("receive failed.");
                return false;
            }
#else
            received_count = read(my_sockfd, buf, 1024);
            if (received_count < 0) {
                LOG_ERROR("receive failed.");
                return false;
            }
#endif

            my_network_buffer.insert(my_network_buffer.end(), buf, buf+received_count);

            // determine where to search from in the next iteration
            beg = my_network_buffer.begin() + dist;
            // delimiters might be in the buffer up to the last element
            // (exclusive) otherwise delimiters would already have been found.
            for (unsigned int i=0;i<delimiters.length()-1;i++) {
                if(beg == my_network_buffer.begin()) break;
                beg--;
            }
        }
    }

    return !error;
}

bool IRCBot::send_message(const std::string &msg)
{
    std::string the_msg = msg;
    the_msg += IRC_LINE_DELIMITERS;

    LOG_INFO("SENDING: " + msg);

#ifdef USE_SFML_SOCKETS
    if (my_socket.send(the_msg.c_str(), the_msg.length()) != sf::Socket::Done)
        return false;
#else
    std::size_t send_count = write(my_sockfd, the_msg.c_str(), the_msg.length());
    if (send_count < 0)
        return false;
#endif
    return true;
}

