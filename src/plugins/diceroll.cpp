#include "../plugin.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class diceRoll : public plugin {
public:
    virtual string call(string command) const
    {
        srand (unsigned(time(NULL)));
	int randomNumber = rand() % 5 + 1;
        string str = to_string(randomNumber);
        return str; // determined by a dice roll
    }
};

// the class factories

extern "C" plugin* create() {
    return new diceRoll;
}

extern "C" void destroy(plugin* p) {
    delete p;
}
