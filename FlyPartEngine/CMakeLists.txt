project(FlyPartRuntime)
cmake_minimum_required(VERSION 2.8)


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
   set(CMAKE_CXX_COMPILER /usr/bin/g++)
   file(GLOB_RECURSE CorePlatformImpl "${CoreDir}/Linux/*")
endif()

set (CMAKE_BUILD_TYPE Debug)

add_library(FlyPartRuntime STATIC ${fpCommonSrc}
                                 ${GenericPlatformSrc}
                                 ${CoreAbstractSrc}
                                 ${CorePlatformImpl})
SET_TARGET_PROPERTIES(FlyPartRuntime PROPERTIES LINKER_LANGUAGE CXX)
SET_TARGET_PROPERTIES(FlyPartRuntime PROPERTIES OUTPUT_NAME FlyPartRuntime)
