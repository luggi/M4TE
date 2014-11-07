#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include <string>
#include <vector>
#include <libconfig.h++>

using namespace std;

class ConfigManager {
    public:
        ConfigManager();

        bool load(string filename);

        bool save(string filename);

        void setDefault();

        // getter
        string getServer() const;
        int getServerport() const;
        string getServerpassword() const;
        vector<string> getChannels() const;
        bool getSsl() const;
        string getUsername() const;
        string getNickservpassword() const;

    private:
        libconfig::Config cfg;

        string server;
        int serverport;
        string serverpassword;
        bool ssl;
        string username;
        string nickservpassword;
        vector<string> channels;
};

#endif
