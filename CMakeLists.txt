# Copyright (C) 2026 Ian Torres
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.30)
project(server)

set(CMAKE_CXX_STANDARD 20)
option(BUILD_TESTS "Build test cases" ON)

add_executable(server main.cpp)

find_package(Boost REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG
        "-O0 -g -fsanitize=address -fno-omit-frame-pointer"
)
set(CMAKE_LINKER_FLAGS_DEBUG
        "-fsanitize=address"
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/objects/*.cpp")

add_library(core OBJECT ${SOURCES})
target_include_directories(core PUBLIC src/include)
target_link_libraries(core ${Boost_LIBRARIES})
target_link_libraries(server $<TARGET_OBJECTS:core>)
target_include_directories(server PRIVATE src/include)

if (BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    file(GLOB_RECURSE TESTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc")
    add_executable(tests ${TESTS})

    target_link_libraries(tests GTest::gtest_main $<TARGET_OBJECTS:core>)
    target_include_directories(tests PRIVATE src/include)
    include(GoogleTest)
    gtest_discover_tests(tests)
endif ()