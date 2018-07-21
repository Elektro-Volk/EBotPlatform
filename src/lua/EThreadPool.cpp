/*
    Copyright Elektro-Volk 2018
    EMail: elektro-volk@yandex.ru
    VK: https://vk.com/ebotp

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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
