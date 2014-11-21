#ifndef __IRC_BOT_H__
#define __IRC_BOT_H__

#include <string>
#include <deque>
#include <SFML/Network.hpp>

#include "ConfigManager.h"

#define IRC_LINE_DELIMITERS "\r\n"

class IRCBot
{
    public:
        IRCBot() = delete;
        IRCBot(const std::string &config_filename);
        bool connect();
        void disconnect();
        void process();
        bool connected();
    private:
        void process_input_line(const std::string &line);
        bool read_until(const std::string &delimiters, std::string &line);

        sf::TcpSocket my_socket;
        bool my_connected;
        std::deque<uint8_t> my_network_buffer;
        ConfigManager my_config_manager;
};

#endif /* __IRC_BOT_H__ */

