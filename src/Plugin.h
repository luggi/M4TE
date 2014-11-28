#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <string>

using namespace std;

// Plugin base class
class plugin {
    public:
        virtual ~plugin() {}

        virtual string call(string command) const = 0;
    private:
        string name;
};

// the types of the class factories
typedef plugin* create_t();
typedef void destroy_t(plugin*);

#endif

