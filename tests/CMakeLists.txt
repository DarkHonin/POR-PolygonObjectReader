cmake_minimum_required (VERSION 3.1)

file(COPY files DESTINATION ${CMAKE_BINARY_DIR}/tests)
add_executable(wfobj.test wfobj.test.cpp)
link_libraries(wfobj.test POR)
