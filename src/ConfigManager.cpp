#include "ConfigManager.h"

#include <string>
#include <vector>

using namespace std;

ConfigManager::ConfigManager()
{
    setDefault();
}

void ConfigManager::load(string filename)
{
    // TODO
}

void ConfigManager::save(string filename)
{
    // TODO
}

void ConfigManager::setDefault()
{
    server = "irc.freenode.net";
    serverport = 6667;
    serverpassword = "";
    channels.clear();
    ssl = false;
    username = "Heaplock-M4TE";
    nickservpassword = "";
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

