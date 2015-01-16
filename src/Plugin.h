#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>

using namespace std;

// plugin base class
class Plugin {
    public:
        virtual ~Plugin() {}

        virtual string call(const string Channel, const string Nick, const string command) = 0;
    private:
        string name;
};

// class factories
typedef Plugin* create_t();
typedef void destroy_t(Plugin*);

#endif
