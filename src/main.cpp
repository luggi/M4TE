#include <iostream>

#include "IRCBot.h"

int main(int argc, char *argv[])
{
    IRCBot irc_bot;
    irc_bot.connect("irc.freenode.net", 6667);

    irc_bot.test();

    irc_bot.disconnect();
    return 0;
}

