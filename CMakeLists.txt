cmake_minimum_required(VERSION 3.13)
project(Artificial_life VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic -Werror -g)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/build")

include_directories(include)

include_directories(src)

# add_library(BinarySearchTree src/BinarySearchTree.cpp)
# target_link_libraries(BinarySearchTree Node)

add_executable(Artificial_life src/artificial_life.cc)
# target_link_libraries(Lab3 BinarySearchTree)
