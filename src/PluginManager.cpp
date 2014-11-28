#include "PluginManager.h"

#include "log.h"
#include "Plugin.h"

#include <map>
#include <memory>
#include <string>

using namespace std;

const vector<string> PluginManager::getPluginNames() const {
    vector<string> names;
    
    for ( map<string, pluginData_t>::iterator it=pluginMap.begin() ; it != pluginMap.end(); ++it )
    {
        names.push_back(it->first);
    }
    
    return names;
}

int pluginManager::onLoad (string name)
{

    string path = "./plugins/" + name + ".so";

   // load a new object
    void* object = dlopen(path.c_str(), RTLD_LAZY);
    if (!object) { // failed to load plugin
        LOG_ERROR("loading plugin " + name + " failed!");
        return -1;
    }
    pluginMap[name].dlopenPtr = object;
    // reset errors
    dlerror();

    // load the symbols
    create_t* create_plugin = (create_t*) dlsym(object, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        LOG_ERROR("plugin " + name + "not valid");
        return -1;
    }

    pluginMap[name].pluginPtr = create_plugin();

    return 0;
}

int pluginManager::onUnload (string name)
{
    const char* dlsym_error;
    destroy_t* destroy_plugin = (destroy_t*) dlsym(pluginMap[name].dlopenPtr, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        return -1;
    }

    destroy_plugin(pluginMap[name].pluginPtr);
    pluginMap.erase(name);
    return 0;
}

int PluginManager::call(string pluginName, string command) {
    // get plugin
    map<string, pluginData_t>::iterator it = plugins.find(pluginName);
    if (it == plugins.end()) {
        LOG_ERROR("plugin " + pluginName + " not loaded");
        return -1;
    }

    // invoke `call()`
    it->second->call();
    return 0;
}
