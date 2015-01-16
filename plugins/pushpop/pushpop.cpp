#include "Plugin.h"

#include <string>

#include "stack.h"

using namespace std;

class Pushpop : public Plugin {

    private:
        Stack<string> stack;

    public:
        Pushpop()
        {
            stack.clear();
        }

        string call(IRCBot &irc_bot, const string channel, const string nick, const string command)
        {
            if (command.find("push ") == 0) {
                string e = command.substr(5);
                stack.push(e);
                return "pushed: " + e;
            } else if (command.find("pop") == 0) {
                if (stack.empty()) {
                    return "stack empty";
                }
                return "pop: " + stack.pop();
            } else if (command.find("clear") == 0) {
                stack.clear();
                return "stack cleared";
            } else {
                return "unknown command, usage: push <string> | pop";
            }
        }
};

extern "C" Plugin* create() {
    return new Pushpop;
}

extern "C" void destroy(Plugin* p) {
    delete p;
}
