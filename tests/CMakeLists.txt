cmake_minimum_required (VERSION 3.1)
find_library(POR REQUIRED)
add_executable(wfobj.test wfobj.test.cpp ${POR_LIBRARIES})

add_test(NAME wfobj_test COMMAND wfobj.test )