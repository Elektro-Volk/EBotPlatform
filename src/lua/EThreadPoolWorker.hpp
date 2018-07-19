#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include "rapidjson/document.h"

class EThreadPoolWorker {
private:
    char id[1];
    bool busy;
    bool enabled;
    
    std::condition_variable cv;
    std::mutex mutex;
    std::thread thread;

    //lua_State* L;

    void loop();
public:
    EThreadPoolWorker();
    bool isBusy();
    void add(rapidjson::Value &msg);
    ~EThreadPoolWorker();
protected:

};
