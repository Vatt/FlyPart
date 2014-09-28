
cmake_minimum_required(3.0)
project(fpSystem)

set(src fpSystemInterface.h)
add_library(fpSystem STATIC ${src})