#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>

using namespace std;

// plugin base class
class plugin {
    public:
        virtual ~plugin() {}

        virtual string call(string command) const = 0;
    private:
        string name;
};

// class factories
typedef plugin* create_t();
typedef void destroy_t(plugin*);

#endif
