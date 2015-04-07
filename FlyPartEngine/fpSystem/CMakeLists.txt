project(fpSystem)
cmake_minimum_required(VERSION 3.0)



INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

set(common_include "../fpCommon/")


file(GLOB_RECURSE SOURCE_DIRS   "${CMAKE_CURRENT_SOURCE_DIR}/*")
set(src)
file(GLOB_RECURSE common "${common_include}/*")




set (CMAKE_BUILD_TYPE Debug)
if ( CMAKE_COMPILER_IS_GNUCXX )

    set(MY_CXX_FLAGS  "-Wall -std=c++11 -fmessage-length=0  -L/usr/local/lib -L/usr/lib")
    set(CMAKE_CXX_FLAGS "-O0 ${MY_CXX_FLAGS}")

    #set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
else ()

endif ()
# message (FATAL_ERROR ${SOURCE_DIRS})
add_library(fpSystem STATIC ${SOURCE_DIRS} ${common})
SET_TARGET_PROPERTIES(fpSystem PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(fpSystem PROPERTIES OUTPUT_NAME fpSystem)
