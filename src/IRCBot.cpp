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
    std::size_t received;
    char buf[4096];
    std::string line;

    sf::Socket::Status status = my_socket.receive(buf, sizeof(buf), received);
    if(sf::Socket::Done != status)
    {
        LOG_ERROR("receive failed.");
        disconnect();
        return;
    }

    my_input_stream << buf;

    while(getline(my_input_stream, line))
    {
        process_input_line(line);
    }

    /* if we get eof, it means \n has not been read and the message is
     * incomplete, so we put the message back to read it later */
    if(my_input_stream.eof())
    {
        my_input_stream << line;
    }
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

void IRCBot::process_input_line(std::string line)
{
    LOG_INFO("<<<<< line start");
    LOG_INFO(line);
    LOG_INFO(">>>>> line end");
}

