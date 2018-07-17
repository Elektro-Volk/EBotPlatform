cmake_minimum_required(VERSION 2.8)
project(EBP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Three party
find_package(CURL REQUIRED)
#include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/tparty/irrlicht/include )

# Engine source files
include_directories( src/ )
include_directories( third_party/rapidjson/include )
include( src/utils/Utils.cmake )
include( src/core/Core.cmake )
# Other
include( src/vk/vk.cmake )

add_executable(EBP ${S_UTILS} ${S_CORE} ${S_VK} )

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(EBP ${CURL_LIBRARIES})
