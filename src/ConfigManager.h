#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include <string>
#include <vector>

using namespace std;

class ConfigManager {
    public:
        ConfigManager();

        void load(string filename);

        void save(string filename);

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
        string server;
        int serverport;
        string serverpassword;
        vector<string> channels;
        bool ssl;
        string username;
        string nickservpassword;
};

#endif
