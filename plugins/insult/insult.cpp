#include "Plugin.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class Insult : public Plugin {

    private:
        static const vector<string> insults;

    public:
        Insult() {
            srand (unsigned(time(NULL)));
        }
        string call(const string channel, const string nick, const string command) const
        {
            int random = rand() % insults.size();
            return insults[random];
        }
};

const vector<string> Insult::insults {
    "Bring it noob. I'll give ya memory errors for life!",
    "Does your ass ever get jealous of the amount of shit that comes out of your mouth?",
    "God must of had a broken gpu when he created you, theres artifacts all over your face.",
    "He's a few patterns short of a regex."
    "I fart in your general direction. Your mother was a hamster and your father smelt of elderberries."
    "I'll ram your body if you keep overclocking my bus.",
    "The long long holding your weight is negative",
    "You are a sad strange little man, and you have my pity.",
    "You fight like a dairy farmer."
    "You running crossfire or are you just s.s.s.stuttering?",
    "You're about as useful as Anne Franks drum kit",
};

extern "C" Plugin* create() {
    return new Insult;
}

extern "C" void destroy(Plugin* p) {
    delete p;
}
