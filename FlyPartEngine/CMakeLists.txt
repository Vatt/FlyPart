project(FlyPartEngine)
cmake_minimum_required(VERSION 3.0)




set(fpCommonDir "${CMAKE_CURRENT_SOURCE_DIR}/fpCommon")
set(CoreDir "${CMAKE_CURRENT_SOURCE_DIR}/Core")
set(GenericPlatformDir "${CoreDir}/GenericPlatform")
set(CoreAbstractDir "${CoreDir}/CoreAbstractLayer")


file(GLOB_RECURSE fpCommonSrc "${fpCommonDir}/*")
file(GLOB_RECURSE GenericPlatformSrc "${GenericPlatformDir}/*")
file(GLOB_RECURSE CoreAbstractSrc "${CoreAbstractDir}/*")


if (WIN32)
    file(GLOB_RECURSE CorePlatformImpl "${CoreDir}/Windows/*")
endif()
if (UNIX)
    file(GLOB_RECURSE CorePlatformImpl "${CoreDir}/Linux/*")
endif()

set (CMAKE_BUILD_TYPE Debug)
if ( CMAKE_COMPILER_IS_GNUCXX )
    set(MY_CXX_FLAGS  "-Wall -std=c++11 -fmessage-length=0  -L/usr/local/lib -L/usr/lib")
    set(CMAKE_CXX_FLAGS "-O0 ${MY_CXX_FLAGS}")
endif ()

add_library(FlyPartEngine STATIC ${fpCommonSrc}
                                 ${GenericPlatformSrc}
                                 ${CoreAbstractSrc}
                                 ${CorePlatformImpl})
SET_TARGET_PROPERTIES(FlyPartEngine PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(FlyPartEngine PROPERTIES OUTPUT_NAME FlyPartEngine)
