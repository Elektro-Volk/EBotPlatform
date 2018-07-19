#include "EThreadPoolWorker.hpp"
#include "ELua.hpp"
#include "core/ENet.hpp"
#include "core/EConsole.hpp"

EThreadPoolWorker::EThreadPoolWorker()
:enabled(true), busy(false), thread(&EThreadPoolWorker::loop, this)
{
    e_net->handles.insert({ thread.get_id(), curl_easy_init() });

    id[0] = e_lua->pool->nWorkers++;
	//L = lua_newthread(luawork::state);
    //lua_setfield(luawork::state, LUA_REGISTRYINDEX, id);
    e_console->log("Поток", "new " + std::to_string(id[0]));
}

void EThreadPoolWorker::loop()
{
    while (enabled) {
        std::unique_lock<std::mutex> locker(mutex);
    	cv.wait(locker, [&](){ return busy || !enabled; });

    	if (!busy) continue;
        /*lua_unlock(L);
        luawork::safeCall(L, 1);
        lua_lock(L);*/
        e_console->log("Поток", "do " + std::to_string(id[0]));
        busy = false;
    }
}

bool EThreadPoolWorker::isBusy()
{
    return busy;
}

void EThreadPoolWorker::add(rapidjson::Value &msg)
{
    std::unique_lock<std::mutex> locker(mutex);
    busy = true;

    /*lua_unlock(L);
    lua_settop(L, 0);
    lua_getglobal(L, "NewMessage");
    lua_json::pushValue(L, msg);
    lua_lock(L);*/
    e_console->log("Поток", "+ " + std::to_string(id[0]));
    cv.notify_one();
}

EThreadPoolWorker::~EThreadPoolWorker()
{
    enabled = false;
    while(busy){}
    curl_easy_cleanup(e_net->handles[thread.get_id()]);
    e_net->handles.erase(thread.get_id());
    cv.notify_one();
    thread.join();
}
