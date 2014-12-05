#include "plugin.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class diceRoll : public plugin {
    public:
        diceRoll()
        {
            srand (unsigned(time(NULL)));
        }

        string call(const string command) const
        {
            int randomNumber = rand() % 5 + 1;
            string str = to_string(randomNumber);
            return str;
        }
};

extern "C" plugin* create() {
    return new diceRoll;
}

extern "C" void destroy(plugin* p) {
    delete p;
}
