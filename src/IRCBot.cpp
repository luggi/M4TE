#include <iostream>

#include "IRCBot.h"

#define LOG_TAG "IRCBot: "
#define LOG_ERROR(msg) std::cerr << LOG_TAG "error: " msg << std::endl;

bool IRCBot::connect(const std::string &ip_address, const unsigned short port)
{
    sf::Socket::Status status = my_socket.connect(ip_address, port);
    if(sf::Socket::Done != status)
    {
        LOG_ERROR("failed to connect.");
        return false;
    }

    return true;
}

void IRCBot::test()
{
    std::size_t received;
    char buf[4096];
    sf::Socket::Status status = my_socket.receive(buf, sizeof(buf), received);
    if(sf::Socket::Done != status)
    {
        LOG_ERROR("receive failed.");
    }
    std::cout << "RECEIVED:" << std::endl;
    std::cout << buf << std::endl;
    std::cout << "END RECEIVED" << std::endl;
}

void IRCBot::disconnect()
{
    my_socket.disconnect();
}

