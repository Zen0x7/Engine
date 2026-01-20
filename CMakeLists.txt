cmake_minimum_required(VERSION 3.30)
project(server)

set(CMAKE_CXX_STANDARD 20)
option(BUILD_TESTS "Build test cases" ON)

add_executable(server main.cpp)

find_package(Boost REQUIRED)
include_directories(src/include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/objects/*.cpp")

add_library(core ${SOURCES})
target_link_libraries(core ${Boost_LIBRARIES})
target_link_libraries(server core)

if (BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    file(GLOB_RECURSE TESTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc")
    add_executable(tests ${TESTS})

    target_link_libraries(tests GTest::gtest_main core)
    include(GoogleTest)
    gtest_discover_tests(tests)
endif ()