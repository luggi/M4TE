#include <iostream>

#include "IRCBot.h"
#include "log.h"

IRCBot::IRCBot(const std::string &config_filename)
{
    my_config_manager.load(config_filename);
}

bool IRCBot::connect()
{
    const std::string &ip_address = my_config_manager.getServer();
    const unsigned short int &port = my_config_manager.getServerport();

    sf::Socket::Status status = my_socket.connect(ip_address, port);
    if(sf::Socket::Done != status)
    {
        LOG_ERROR("failed to connect.");
        my_connected = false;
        return false;
    }

    my_connected = true;

    return true;
}

bool IRCBot::login()
{
    const std::string &nick = my_config_manager.getUsername();

    if(!send_message("NICK " + nick + IRC_LINE_DELIMITERS))
    {
        return false;
    }

    // http://stackoverflow.com/questions/5199808/irc-user-message-makes-no-sense-to-me
    if(!send_message("USER " + nick + " localhost * :" + nick + IRC_LINE_DELIMITERS))
    {
        return false;
    }

    return true;
}

bool IRCBot::process()
{
    std::string line;

    if(!read_until(IRC_LINE_DELIMITERS, line))
    {
        disconnect();
        return false;
    }

    process_input_line(line);

    return true;
}

void IRCBot::disconnect()
{
    my_socket.disconnect();
    my_connected = false;
}

bool IRCBot::connected()
{
    return my_connected;
}

void IRCBot::process_input_line(const std::string &line)
{
    LOG_INFO("<<<<< line start");
    LOG_INFO(line);
    LOG_INFO(">>>>> line end");
}

bool IRCBot::read_until(const std::string &delimiters, std::string &line)
{
    bool error = false;

    auto beg = my_network_buffer.begin();

    while(!error)
    {
        auto pos = std::search(beg, my_network_buffer.end(),
                               delimiters.begin(), delimiters.end());

        if(pos != my_network_buffer.end())
        {
            // delimiters found, return with data
            std::string l(my_network_buffer.begin(), pos); /* ignore delimiters */
            my_network_buffer.erase(my_network_buffer.begin(),pos+delimiters.length());
            line = l;
            return true;
        }
        else
        {
            // need to get more data
            char buf[1024];
            std::size_t received_count;

            // store distance, to later determine where to search from
            // (we don't want the whole buffer to be searched again
            // because we can skip stuff that has already been searched
            // through)
            auto dist = std::distance(my_network_buffer.begin(), my_network_buffer.end());

            if(my_socket.receive(buf, sizeof(buf), received_count) != sf::Socket::Done)
            {
                LOG_ERROR("receive failed.");
                return false;
            }

            my_network_buffer.insert(my_network_buffer.end(), buf, buf+received_count);

            // determine where to search from in the next iteration
            beg = my_network_buffer.begin() + dist;
            // delimiters might be in the buffer up to the last element
            // (exclusive) otherwise delimiters would already have been found.
            for(unsigned int i=0;i<delimiters.length()-1;i++)
            {
                if(beg == my_network_buffer.begin()) break;
                beg--;
            }
        }
    }

    return !error;
}

bool IRCBot::send_message(const std::string &msg)
{
    LOG_INFO("sending...");
    LOG_INFO(msg);
    LOG_INFO("end sending");
    if(my_socket.send(msg.c_str(), msg.length()) != sf::Socket::Done)
    {
        return false;
    }
    return true;
}

