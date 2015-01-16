#include "Plugin.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Remind : public Plugin {
    public:
        Remind()
        { }

        string call(const string channel, const string nick, const string command)
        {
            return "This has to be implemented some time...";
        }
};

extern "C" Plugin* create() {
    return new Remind;
}

extern "C" void destroy(Plugin* p) {
    delete p;
}
