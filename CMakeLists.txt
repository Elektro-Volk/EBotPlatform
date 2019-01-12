cmake_minimum_required(VERSION 2.8)
project(EBP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS "-std=c++11")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set ( CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu/cmake/ )

# Three party
find_package(CURL REQUIRED)
find_package(cpprestsdk REQUIRED NAMES cpprestsdk cpprest)

set( MYSQL_INCLUDE_DIRS "-" )
set( MYSQL_LIBRARIES "-" )

mark_as_advanced( MYSQL_INCLUDE_DIR MYSQL_LIBRARY )


link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/build )

include_directories( ${CURL_INCLUDE_DIR} )
include_directories( ${MYSQL_INCLUDE_DIR} )
include_directories( third_party/lua/src )
include_directories( third_party/rapidjson/include )
include_directories( third_party/sqlite-snapshot-201812251117 )

# Engine source files
include_directories( src/ )
include( src/utils/Utils.cmake )
include( src/core/Core.cmake )
# Other
include( src/vk/vk.cmake )
include( src/lua/lua.cmake )

add_executable(EBP ${S_UTILS} ${S_CORE} ${S_VK} ${S_LUA} third_party/sqlite-snapshot-201812251117/sqlite3.c )

IF (WIN32)
  target_link_libraries(EBP ${CURL_LIBRARIES} ${MYSQL_LIBRARY} lua cpprestsdk::cpprest)
ELSE()
  target_link_libraries(EBP ${CURL_LIBRARIES} mysqlclient dl pthread lua cpprestsdk::cpprest boost_system)
ENDIF()
