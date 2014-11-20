#ifndef __IRC_BOT_H__
#define __IRC_BOT_H__

#include <string>
#include <deque>
#include <SFML/Network.hpp>

#define IRC_LINE_DELIMITERS "\r\n"

class IRCBot
{
    public:
        bool connect(const std::string &ip_address, const unsigned short port);
        void disconnect();
        void process();
        bool connected();
    private:
        void process_input_line(const std::string &line);
        bool read_until(const std::string &delimiters, std::string &line);

        sf::TcpSocket my_socket;
        bool my_connected;
        std::deque<uint8_t> my_network_buffer;
};

#endif /* __IRC_BOT_H__ */

