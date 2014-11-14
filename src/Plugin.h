#ifndef PLUGIN_H_
#define PLUGIN_H_

// Plugin base class
class Plugin {
    public:
        virtual void call() = 0;
        virtual void onLoad();
        virtual void onUnload();
};

#endif
