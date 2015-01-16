#include "PluginManager.h"

#include "log.h"
#include "Plugin.h"

#include <algorithm>
#include <glob.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <dlfcn.h>

using namespace std;

// from: http://stackoverflow.com/a/24703135
vector<string> globVector(const string& pattern){
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> files;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        files.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
}

PluginManager::PluginManager() {
    vector<string> files = globVector("./plugins/*.so");
    
    for (auto &name : files) {
        name = name.substr(((std::string)"./plugins/").length());
        name.erase(name.find(".so"));
        LOG_INFO("loading plugin " + name);
        load(name);
    }
}

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
        LOG_ERROR("loading plugin " + path + " failed! " + dlerror());
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


std::string PluginManager::call(IRCBot &irc_bot, const string pluginName,const string channel, const string nick, const string command) {
    std::string plugin_name_lower = pluginName;
    std::transform(plugin_name_lower.begin(), plugin_name_lower.end(), plugin_name_lower.begin(), ::tolower);

    // get plugin
    auto it = my_plugins.find(plugin_name_lower);
    if (it == my_plugins.end()) {
        LOG_ERROR("plugin " + plugin_name_lower + " not loaded");
        return "";
    }

    // invoke `call()`
    return it->second.pluginPtr->call(irc_bot, channel, nick, command);
}
