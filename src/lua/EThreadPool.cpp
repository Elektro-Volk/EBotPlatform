//
//  EThreadPool.cpp
//  EBotPlatform
//
//  Created by Elektro-Volk on 17/07/2018.
//
//

#include "EThreadPool.hpp"
#include "ELua.hpp"
#include "core/EConsole.hpp"

EThreadPool::EThreadPool()
{
    int pool_count = e_lua->pool_count->getInt();

    for(int i = 0; i < pool_count; i++)
        workers.push_back(new EThreadPoolWorker());

    if (pool_count > 1)
        e_console->log("POOL", "Создано " + std::to_string(pool_count) + " потока.");
}

void EThreadPool::add(rapidjson::Value &msg)
{
    // find free pool and add msg then
    EThreadPoolWorker *freeWorker = nullptr;
    while(!freeWorker){
        for(int i = 0; i < workers.size(); i++) {
            if(workers[i]->isBusy()) continue;
            freeWorker = workers[i];
            break;
        }
    }
    freeWorker->add(msg);
}

EThreadPool::~EThreadPool()
{

}
