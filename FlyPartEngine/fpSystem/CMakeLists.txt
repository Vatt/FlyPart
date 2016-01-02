project(fpSystem)
cmake_minimum_required(VERSION 3.0)



INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

set(common_include "../fpCommon/")
set(platform_src)

file(GLOB_RECURSE generic_memory "${CMAKE_CURRENT_SOURCE_DIR}/Memory/*")
file(GLOB_RECURSE generic_wnd_sys "${CMAKE_CURRENT_SOURCE_DIR}/WindowSystem/*")
file(GLOB_RECURSE generic_input "${CMAKE_CURRENT_SOURCE_DIR}/Input/*")
file(GLOB_RECURSE common_src "${common_include}/*")

if (WIN32)
    file(GLOB_RECURSE platform_src "${CMAKE_CURRENT_SOURCE_DIR}/impl/windows/*")
elseif(UNIX)
    file(GLOB_RECURSE platform_src "${CMAKE_CURRENT_SOURCE_DIR}/impl/linux/*")
else()
    message(FATAL_ERROR "OS not detected")
endif()
set (CMAKE_BUILD_TYPE Debug)
if ( CMAKE_COMPILER_IS_GNUCXX )

    set(MY_CXX_FLAGS  "-Wall -std=c++11 -fmessage-length=0  -L/usr/local/lib -L/usr/lib")
    set(CMAKE_CXX_FLAGS "-O0 ${MY_CXX_FLAGS}")

    #set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
else ()

endif ()

add_library(fpSystem STATIC fpSystemInterface.h ${platform_src}
            ${generic_memory} ${generic_wnd_sys} ${generic_input} ${common_src})
SET_TARGET_PROPERTIES(fpSystem PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(fpSystem PROPERTIES OUTPUT_NAME fpSystem)
