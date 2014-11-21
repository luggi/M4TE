#include <iostream>

#include "IRCBot.h"

int main(int argc, char *argv[])
{
    IRCBot irc_bot("config");

    irc_bot.connect();

    while(irc_bot.connected())
    {
        irc_bot.process();
    }

    irc_bot.disconnect();
    return 0;
}

