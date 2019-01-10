# LUA API
set( LUA_API_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/lua/api )
set( S_LUA_API
    ${LUA_API_PATH}/ln_cmd.cpp
    ${LUA_API_PATH}/ln_console.cpp
    ${LUA_API_PATH}/ln_cvars.cpp
    ${LUA_API_PATH}/ln_fs.cpp
    ${LUA_API_PATH}/ln_mysql.cpp
    ${LUA_API_PATH}/ln_sqlite.cpp
    ${LUA_API_PATH}/ln_net.cpp
    ${LUA_API_PATH}/ln_vkapi.cpp
    ${LUA_API_PATH}/lu_json.cpp
    ${LUA_API_PATH}/lu_other.cpp
    ${LUA_API_PATH}/lu_string.cpp
    ${LUA_API_PATH}/luaapi.cpp
)

set( LUA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/lua/ )
set( S_LUA
    ${LUA_PATH}/ELua.cpp
    ${LUA_PATH}/ELuaState.cpp
    ${LUA_PATH}/EThreadPool.cpp
    ${LUA_PATH}/EThreadPoolWorker.cpp
    ${LUA_PATH}/ELuaJson.cpp
    ${LUA_PATH}/ELuaModules.cpp
    ${S_LUA_API}
)
