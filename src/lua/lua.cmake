set( LUA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/lua/ )
set( S_LUA
    ${LUA_PATH}/ELua.cpp
    ${LUA_PATH}/ELuaState.cpp
    ${LUA_PATH}/EThreadPool.cpp
    ${LUA_PATH}/EThreadPoolWorker.cpp
)
