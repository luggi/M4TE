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

bool ConfigManager::load(const string filename)
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
        channels.clear();
        for (int i = 0; i < chans.getLength(); i++) {
            channels.push_back(chans[i]);
        }
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
    channels = {"#heaplock"};
}

const string ConfigManager::getServer() const
{
    return server;
}

const int ConfigManager::getServerport() const
{
    return serverport;
}

const string ConfigManager::getServerpassword() const
{
    return serverpassword;
}

const vector<string> ConfigManager::getChannels() const
{
    return channels;
}

const bool ConfigManager::getSsl() const
{
    return ssl;
}

const string ConfigManager::getUsername() const
{
    return username;
}

const string ConfigManager::getNickservpassword() const
{
    return nickservpassword;
}
