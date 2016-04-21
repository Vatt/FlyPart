project(fpTest)
cmake_minimum_required(VERSION 3.0)
set (CMAKE_BUILD_TYPE Debug)

if ( CMAKE_COMPILER_IS_GNUCXX )
    set(MY_CXX_FLAGS  "-Wall -std=c++11 -fmessage-length=0   -Wattributes -L/usr/local/lib -L/usr/lib " )
    set(CMAKE_CXX_FLAGS "-O0 ${MY_CXX_FLAGS}")
    #target_link_libraries(test FlyPartEngine)
endif ()


add_executable(fpTest "${CMAKE_CURRENT_SOURCE_DIR}/test.cpp")
SET_TARGET_PROPERTIES(fpTest PROPERTIES LINKER_LANGUAGE CXX)