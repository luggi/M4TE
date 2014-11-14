#include "PluginManager.h"

#include "log.h"
#include "Plugin.h"

#include <map>
#include <memory>
#include <string>

using namespace std;

const map<string, shared_ptr<Plugin>> PluginManager::getPlugins() const {
    return plugins;
}

void PluginManager::load(string pluginName) {
    // TODO
}

void PluginManager::unload(string pluginName) {
    // TODO
}

void PluginManager::call(string pluginName, string command) {
    // get plugin
    map<string, shared_ptr<Plugin>>::iterator it = plugins.find(pluginName);
    if (it == plugins.end()) {
        LOG_ERROR("plugin " + pluginName + " not loaded");
        return;
    }

    // invoke `call()`
    it->second->call();
}
