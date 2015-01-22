#include "Plugin.h"

#include <iostream>
#include <chrono>
#include <random>

using namespace std;

class DiceRoll : public Plugin {
    private:
        default_random_engine generator;
        uniform_int_distribution<int> distribution;

    public:
        DiceRoll() : generator(std::chrono::system_clock::now().time_since_epoch().count()), distribution(1,6) {
        }

        string call(IRCBot &irc_bot, const string channel, const string nick, const string command)
        {
            int randomNumber = distribution(generator);
            string str = to_string(randomNumber);
            return str;
        }
};

extern "C" Plugin* create() {
    return new DiceRoll;
}

extern "C" void destroy(Plugin* p) {
    delete p;
}
