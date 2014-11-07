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
    sf::Socket::Status status = my_socket.receive(buf, sizeof(buf), received);
    if(sf::Socket::Done != status)
    {
        LOG_ERROR("receive failed.");
        disconnect();
        return;
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

