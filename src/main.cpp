#include <iostream>

#include "log.h"
#include "IRCBot.h"

int main(int argc, char *argv[])
{
    IRCBot irc_bot("config");

    irc_bot.connect();

    if(!irc_bot.connected())
    {
        LOG_ERROR("failed to connect");
        return -1;
    }

    if(!irc_bot.login())
    {
        LOG_ERROR("failed to login");
        return -1;
    }

    while(irc_bot.connected())
    {
        if(!irc_bot.process())
        {
            LOG_ERROR("processing network data failed");
            return -1;
        }
    }

    irc_bot.disconnect();
    return 0;
}

