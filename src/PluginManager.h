#ifndef PLUGINMANAGER_H_
#define PLUGINMANAGER_H_

#include "Plugin.h"

#include <map>
#include <memory>
#include <string>

using namespace std;

class PluginManager {
    public:
        const map<string, shared_ptr<Plugin>> getPlugins() const;
        void load(string pluginName);
        void unload(string pluginName);
        void call(string pluginName, string command);

    private:
        map<string, shared_ptr<Plugin>> plugins;

};

#endif
