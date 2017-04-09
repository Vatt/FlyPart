project(fpTest)
cmake_minimum_required(VERSION 2.8)
set (CMAKE_BUILD_TYPE Debug)

if ( CMAKE_COMPILER_IS_GNUCXX )
    set(MY_CXX_FLAGS  "-Wall -std=c++11 -fmessage-length=0   -Wattributes -L/usr/local/lib -L/usr/lib " )
    set(CMAKE_CXX_FLAGS "-O0 ${MY_CXX_FLAGS} -m64 -mcmodel=large")

endif ()
file(GLOB_RECURSE Src "${CMAKE_CURRENT_SOURCE_DIR}/*")
add_executable(fpTest ${Src})
target_link_libraries(fpTest ${CMAKE_SOURCE_DIR}/../Build/FlyPartRuntime/Debug/libFlyPartRuntime.a)
