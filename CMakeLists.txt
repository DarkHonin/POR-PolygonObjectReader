cmake_minimum_required (VERSION 3.1)
project (POR)

enable_testing()

set (POR_VERSION_MAJOR 1)
set (POR_VERSION_MINOR 0)

find_library(glm REQUIRED)

set (CXX_STANDARD c++17)

include_directories(include)
include_directories(${GLM_INCLUDE_DIRECTORIES})

file(GLOB POR_SRC "src/*.cpp")

configure_file (
	"${PROJECT_SOURCE_DIR}/POR.cfg.h"
	"${PROJECT_SOURCE_DIR}/include/POR.cfg.h"
)


add_library(POR ${POR_SRC})
link_libraries(POR ${GLM_LIBRARIES})

add_subdirectory(tests)

link_libraries(wfobj.test POR)

add_test(NAME wfobj_test COMMAND wfobj.test )
