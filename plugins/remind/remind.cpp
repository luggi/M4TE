#include "Plugin.h"
#include "IRCBot.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>

using namespace std;

class Remind : public Plugin {
    public:
        Remind()
        { }
        
        void send_message_later(IRCBot &irc_bot, const string channel, const string nick, int reminderDuration)
        {
        chrono::milliseconds dura(reminderDuration * 1000);
        this_thread::sleep_for(dura);
        
        irc_bot.send_message("PRIVMSG " + channel + " :" + nick + ": I was told to remind you" + to_string(reminderDuration) + " seconds ago");
        }

        string call(IRCBot &irc_bot, const string channel, const string nick, const string command) 
        {
        int seconds;
        
        auto delim = command.find(" ");
        string time = command.substr(0, delim);
        
        try {
            seconds = stoi(time);
        } catch (const invalid_argument &e) {
            // log invalid argument
            return "wrong argument! usage: !remind [duration in seconds]";
        } catch (const out_of_range &e) {
            // log out of range
            return "wrong argument! usage: !remind [duration in seconds]";
        }
        
        std::thread (&Remind::send_message_later, Remind(), std::ref(irc_bot), channel, nick, seconds);

            return "Will remind you in" + to_string(seconds) + "seconds.";
        }
};

extern "C" Plugin* create() {
    return new Remind;
}

extern "C" void destroy(Plugin* p) {
    delete p;
}
