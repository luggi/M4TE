#ifndef __IRC_BOT_H__
#define __IRC_BOT_H__

#include <string>
#include <deque>

#ifdef USE_SFML_SOCKETS
#include <SFML/Network.hpp>
#endif

#include "configManager.h"

#define IRC_LINE_DELIMITERS "\r\n"

class IRCBot
{
    public:
        IRCBot() = delete;
        IRCBot(const std::string &config_filename);
        bool connect();
        bool login();
        void disconnect();
        bool process();
        bool connected();
        void join_channels();

        void wait_for_notice();
        void wait_for_motd();
    private:
        void process_input_line(const std::string &line);
        bool read_until(const std::string &delimiters, std::string &line);
        bool send_message(const std::string &msg);

#ifdef USE_SFML_SOCKETS
        sf::TcpSocket my_socket;
#else
        int my_sockfd;
#endif
        bool my_connected;
        bool my_notice_received;
        bool my_motd_received;
        std::deque<uint8_t> my_network_buffer;
        configManager my_config_manager;
};

#endif /* __IRC_BOT_H__ */

