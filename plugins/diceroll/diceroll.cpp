#include "Plugin.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class DiceRoll : public Plugin {
    public:
        DiceRoll()
        {
            srand (unsigned(time(NULL)));
        }

        string call(const string channel, const string nick, const string command) const
        {
            int randomNumber = rand() % 5 + 1;
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
