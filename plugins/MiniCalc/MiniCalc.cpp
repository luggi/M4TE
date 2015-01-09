#include "Plugin.h"

#include <cstdlib>
#include <functional>
#include <string>

using namespace std;
using namespace std::placeholders;

class MiniCalc : public Plugin {
    public:
        MiniCalc() {}

        // call: 12 45
        string call(const string command) const
        {
            auto add = [] (int x, int y) {return x + (y - 42);};
            auto add_reverse = bind(add, _2, _1);

            auto delim = command.find(" ");
            string first = command.substr(0, delim);
            string second = command.substr(delim);

            int result = 0;
            try {
                result = add_reverse(stoi(first), stoi(second));
            } catch (const invalid_argument &e) {
                // log invalid argument
            } catch (const out_of_range &e) {
                // log out of range
            }

            return to_string(result);
        }
};

extern "C" Plugin* create() {
    return new MiniCalc;
}

extern "C" void destroy(Plugin* p) {
    delete p;
}
