#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "Plugin.h"

#include <map>
#include <memory>
#include <vector>
#include <string>

using namespace std;

struct pluginData {
    void *dlopenPtr;
    Plugin *pluginPtr;
};

class PluginManager {
    public:
        PluginManager();
        ~PluginManager();

        const vector<string> getPluginNames() const;
        int load(const string pluginName);
        int unload(const string pluginName);
        std::string call(IRCBot &irc_bot, const string pluginName, const string channel, const string nick, const string command);

    private:
        map<string, pluginData> my_plugins;
};

#endif
