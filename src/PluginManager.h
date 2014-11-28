#ifndef PLUGINMANAGER_H_
#define PLUGINMANAGER_H_

#include "Plugin.h"

#include <map>
#include <memory>
#include <vector>
#include <string>

using namespace std;

typedef struct pluginData_t {
    void* dlopenPtr;
    plugin* pluginPtr;
} pluginData_t;

class PluginManager {
    public:
        const vector<string> getPluginNames() const;
        int onLoad(string pluginName);
        int onUnload(string pluginName);
        int call(string pluginName, string command);

    private:
        map<string, pluginData_t> my_plugins;
};

#endif
