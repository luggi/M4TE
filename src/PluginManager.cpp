#include "PluginManager.h"

#include "log.h"
#include "Plugin.h"

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <dlfcn.h>

using namespace std;

PluginManager::~PluginManager() {
    for (auto &name : getPluginNames()) {
        unload(name);
    }
}

const vector<string> PluginManager::getPluginNames() const {
    vector<string> names;

    for (auto &it : my_plugins) {
        names.push_back(it.first);
    }

    return names;
}

int PluginManager::load(const string name) {
    string path = "./plugins/" + name + ".so";

    // load a new object
    void* object = dlopen(path.c_str(), RTLD_LAZY);
    if (!object) {
        // failed to load plugin
        LOG_ERROR("loading plugin " + path + " failed!");
        return -1;
    }
    my_plugins[name].dlopenPtr = object;

    // reset errors
    dlerror();

    // load the symbols
    create_t* create_plugin = (create_t*) dlsym(object, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        LOG_ERROR("plugin " + name + "not valid");
        return -1;
    }

    my_plugins[name].pluginPtr = create_plugin();

    return 0;
}

int PluginManager::unload (const string name) {
    const char* dlsym_error;
    destroy_t* destroy_plugin = (destroy_t*) dlsym(my_plugins[name].dlopenPtr, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error)
        return -1;

    destroy_plugin(my_plugins[name].pluginPtr);
    my_plugins.erase(name);
    return 0;
}

int PluginManager::call(const string pluginName, const string command) {
    std::string plugin_name_lower = pluginName;
    std::transform(plugin_name_lower.begin(), plugin_name_lower.end(), plugin_name_lower.begin(), ::tolower);

    // get plugin
    auto it = my_plugins.find(plugin_name_lower);
    if (it == my_plugins.end()) {
        LOG_ERROR("plugin " + plugin_name_lower + " not loaded");
        return -1;
    }

    // invoke `call()`
    it->second.pluginPtr->call(command);
    return 0;
}
