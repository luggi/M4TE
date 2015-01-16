#include "Plugin.h"

#include <iostream>
#include <random>

using namespace std;

class DiceRoll : public Plugin {
    private:
        static default_random_engine generator;
        static uniform_int_distribution<int> distribution;


    public:
        DiceRoll() {
        }

        string call(IRCBot &irc_bot, const string channel, const string nick, const string command)
        {
            int randomNumber = distribution(generator);
            string str = to_string(randomNumber);
            return str;
        }
};

uniform_int_distribution<int> DiceRoll::distribution(1, 6);
default_random_engine DiceRoll::generator;

extern "C" Plugin* create() {
    return new DiceRoll;
}

extern "C" void destroy(Plugin* p) {
    delete p;
}
