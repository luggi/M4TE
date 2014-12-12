#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <vector>
#include <libconfig.h++>

using namespace std;

class ConfigManager {
    public:
        // using default settings
        ConfigManager();

        bool load(const string filename);

        // getter
        const string getServer() const;
        const int getServerport() const;
        const string getServerpassword() const;
        const vector<string> getChannels() const;
        const bool getSsl() const;
        const string getUsername() const;
        const string getNickservpassword() const;

    private:
        libconfig::Config cfg;

        string server;
        int serverport;
        string serverpassword;
        bool ssl;
        string username;
        string nickservpassword;
        vector<string> channels;

        void setDefault();
};

#endif
