#include "ConfigManager.h"

#include "log.h"

#include <string>
#include <vector>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;

ConfigManager::ConfigManager()
{
    setDefault();
}

bool ConfigManager::load(string filename)
{
    try {
        cfg.readFile(filename.c_str());
    } catch (ParseException e) {
        LOG_ERROR("config file not valid, using defaults");
        return false;
    } catch (FileIOException e) {
        LOG_ERROR("config file not present, using defaults");
        return false;
    }

    cfg.lookupValue("server", server);
    cfg.lookupValue("serverport", serverport);
    cfg.lookupValue("serverpassword", serverpassword);
    cfg.lookupValue("ssl", ssl);
    cfg.lookupValue("username", username);
    cfg.lookupValue("nickservpassword", nickservpassword);

    if (cfg.exists("channels") && cfg.lookup("channels").isArray()) {
        Setting &chans = cfg.lookup("channels");
        for (int i = 0; i < chans.getLength(); i++) {
            channels.push_back(chans[i]);
        }
    }

    return true;
}

bool ConfigManager::save(string filename)
{
    Setting &root = cfg.getRoot();

    if (!root.exists("server")) {
        root.add("server", Setting::TypeString);
    }
    root["server"] = server;

    if (!root.exists("serverport")) {
        root.add("serverport", Setting::TypeInt);
    }
    root["serverport"] = serverport;

    if (!root.exists("serverpassword")) {
        root.add("serverpassword", Setting::TypeString);
    }
    root["serverpassword"] = serverpassword;

    if (!root.exists("ssl")) {
        root.add("ssl", Setting::TypeBoolean);
    }
    root["ssl"] = ssl;

    if (!root.exists("username")) {
        root.add("username", Setting::TypeString);
    }
    root["username"] = username;

    if (!root.exists("nickservpassword")) {
        root.add("nickservpassword", Setting::TypeString);
    }
    root["nickservpassword"] = nickservpassword;

    if (root.exists("channels")) {
        root.remove("channels");
    }
    Setting &chan = root.add("channels", Setting::TypeArray);
    for (string c : channels) {
        chan.add(Setting::TypeString) = c;
    }

    try {
        cfg.writeFile(filename.c_str());
    } catch (FileIOException e) {
        LOG_ERROR("could not write config file");
        return false;
    }

    return true;
}

void ConfigManager::setDefault()
{
    server = "irc.freenode.net";
    serverport = 6667;
    serverpassword = "";
    ssl = false;
    username = "Heaplock-M4TE";
    nickservpassword = "";

    channels.clear();
    channels = {"#itsyndikat", "#heaplock"};
}

string ConfigManager::getServer() const
{
    return server;
}

int ConfigManager::getServerport() const
{
    return serverport;
}

string ConfigManager::getServerpassword() const
{
    return serverpassword;
}

vector<string> ConfigManager::getChannels() const
{
    return channels;
}

bool ConfigManager::getSsl() const
{
    return ssl;
}

string ConfigManager::getUsername() const
{
    return username;
}

string ConfigManager::getNickservpassword() const
{
    return nickservpassword;
}

