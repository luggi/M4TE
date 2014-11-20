#include <iostream>

#include "IRCBot.h"
#include "log.h"

bool IRCBot::connect(const std::string &ip_address, const unsigned short port)
{
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

void IRCBot::process()
{
    std::string line;

    if(!read_until(IRC_LINE_DELIMITERS, line))
    {
        disconnect();
        return;
    }

    process_input_line(line);
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

