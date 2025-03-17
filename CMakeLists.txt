cmake_minimum_required(VERSION 3.10.0)
project(SearchingAlgorithms VERSION 0.1.0 LANGUAGES C CXX)
add_compile_options(-Wall -Wextra -O2 --std=gnu++20)

add_executable(SearchingAlgorithms src/NsqPuzzle/execute.cpp)
add_executable(DataCreation problems/NsqPuzzle/DataCreation.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set_property(TARGET SearchingAlgorithms PROPERTY CXX_STANDARD 20)

enable_testing()
add_executable(cpp_test test/NsqPuzzle/test.cpp)
add_test(NAME N_Odd COMMAND cpp_test --n 3)
add_test(NAME N_Even COMMAND cpp_test --n 4)