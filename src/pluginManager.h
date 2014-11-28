#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "plugin.h"

#include <map>
#include <memory>
#include <vector>
#include <string>

using namespace std;

struct pluginData {
    void *dlopenPtr;
    plugin *pluginPtr;
};

class pluginManager {
    public:
        ~pluginManager();

        const vector<string> getPluginNames() const;
        int load(const string pluginName);
        int unload(const string pluginName);
        int call(const string pluginName, const string command);

    private:
        map<string, pluginData> my_plugins;
};

#endif
