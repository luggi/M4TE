#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "Plugin.h"

#include <glob.h>
#include <map>
#include <memory>
#include <vector>
#include <string>

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

struct pluginData {
    void *dlopenPtr;
    Plugin *pluginPtr;
};

class PluginManager {
    public:
        ~PluginManager();

        const vector<string> getPluginNames() const;
        int load(const string pluginName);
        int unload(const string pluginName);
        std::string call(const string pluginName, const string channel, const string nick, const string command);

    private:
        map<string, pluginData> my_plugins;
};

#endif
