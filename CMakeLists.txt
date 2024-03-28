cmake_minimum_required(VERSION 3.27)
project(YellowBelt)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_subdirectory(TestRunner)
add_subdirectory(MatrixSummation)