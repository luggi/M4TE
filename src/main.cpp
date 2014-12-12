#include <iostream>

#include <signal.h>

#include "log.h"
#include "IRCBot.h"

volatile sig_atomic_t sigint_received = 0;

void signal_handler(int s)
{
    sigint_received = 1;
}

int main(int argc, char *argv[])
{
    IRCBot irc_bot("config");

    signal(SIGINT, signal_handler);

    irc_bot.connect();

    if (!irc_bot.connected()) {
        LOG_ERROR("failed to connect");
        return -1;
    }

    irc_bot.wait_for_notice();

    if (!irc_bot.login()) {
        LOG_ERROR("failed to login");
        return -1;
    }

    irc_bot.wait_for_motd();

    irc_bot.join_channels();

    while (irc_bot.connected()) {
        if(sigint_received)
            break;

        if (!irc_bot.process()) {
            LOG_ERROR("processing network data failed");
            return -1;
        }
    }

    irc_bot.disconnect();
    return 0;
}

