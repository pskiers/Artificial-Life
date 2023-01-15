cmake_minimum_required(VERSION 3.13)
project(Artificial_life VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(-Wall -Wextra -pedantic -Werror -g)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/build")

find_package(Qt5 REQUIRED COMPONENTS Widgets)

include_directories(app)
include_directories(include)
include_directories(src)
include_directories(tests)

file(
  GLOB SRCS
  include/*.h
  src/*.cc
)

add_library(app_library ${SRCS})

file(
  GLOB APPS
  app/*.cc
  app/src/*.cc
  app/include/*.h
  app/qui/*.ui
)

add_executable(artificial_life ${APPS})
target_link_libraries(artificial_life PRIVATE app_library)
target_link_libraries(artificial_life PRIVATE Qt5::Widgets)

set_target_properties(artificial_life PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

# Fetch gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(
  GLOB TESTS
  tests/*.cc
)

add_executable(
  tests
  ${TESTS}
)
target_link_libraries(
  tests
  GTest::gtest_main
  app_library
)

include(GoogleTest)
gtest_discover_tests(tests)
