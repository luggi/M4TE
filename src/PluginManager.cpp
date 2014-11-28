#include "PluginManager.h"

#include "log.h"
#include "Plugin.h"

#include <map>
#include <memory>
#include <vector>
#include <string>

#include <dlfcn.h>

using namespace std;

const vector<string> PluginManager::getPluginNames() const {
    vector<string> names;
    
    for ( auto it=my_plugins.begin() ; it != my_plugins.end(); ++it )
    {
        names.push_back(it->first);
    }
    
    return names;
}

int PluginManager::onLoad (string name)
{

    string path = "./plugins/" + name + ".so";

   // load a new object
    void* object = dlopen(path.c_str(), RTLD_LAZY);
    if (!object) { // failed to load plugin
        LOG_ERROR("loading plugin " + name + " failed!");
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

int PluginManager::onUnload (string name)
{
    const char* dlsym_error;
    destroy_t* destroy_plugin = (destroy_t*) dlsym(my_plugins[name].dlopenPtr, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        return -1;
    }

    destroy_plugin(my_plugins[name].pluginPtr);
    my_plugins.erase(name);
    return 0;
}

int PluginManager::call(string pluginName, string command) {
    // get plugin
    auto it = my_plugins.find(pluginName);
    if (it == my_plugins.end()) {
        LOG_ERROR("plugin " + pluginName + " not loaded");
        return -1;
    }

    // invoke `call()`
    it->second.pluginPtr->call(command);
    return 0;
}
