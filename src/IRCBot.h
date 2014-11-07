#ifndef __IRC_BOT_H__
#define __IRC_BOT_H__

#include <SFML/Network.hpp>

class IRCBot
{
    public:
        bool connect(const std::string &ip_address, const unsigned short port);
        void disconnect();
        void process();
        bool connected();
    private:
        sf::TcpSocket my_socket;
        bool my_connected;
};

#endif /* __IRC_BOT_H__ */

