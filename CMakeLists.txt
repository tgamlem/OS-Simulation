cmake_minimum_required(VERSION 3.0)

project(os-sim)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
include_directories(AFTER PRIVATE headers)
file(GLOB os-sim-source
	"source/*.cpp"
)

add_executable(main ${os-sim-source})
