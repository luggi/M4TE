#ifndef __IRC_BOT_H__
#define __IRC_BOT_H__

#include <sstream>
#include <SFML/Network.hpp>

class IRCBot
{
    public:
        bool connect(const std::string &ip_address, const unsigned short port);
        void disconnect();
        void process();
        bool connected();
    private:
        void process_input_line(std::string line);
        sf::TcpSocket my_socket;
        bool my_connected;
        std::stringstream my_input_stream;
};

#endif /* __IRC_BOT_H__ */

