cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)
include(ExternalProject)

project(SO2_Project)
enable_testing()

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)

set(PROJECT_LOG_FOLDER ${PROJECT_SOURCE_DIR}/logs)

set(ERROR_FLAGS "-Wall -Werror -Wextra -Wfatal-errors -pedantic-errors")

set(GTEST_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/gtest)
set(SFML_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/sfml)
set(SPDLOG_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/spdlog)

ExternalProject_Add(GTEST
        GIT_REPOSITORY https://github.com/google/googletest
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${GTEST_INSTALL_LOCATION}
        )
ExternalProject_Add(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SFML_INSTALL_LOCATION}
        )
ExternalProject_Add(SPDLOG
        GIT_REPOSITORY https://github.com/gabime/spdlog
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SPDLOG_INSTALL_LOCATION}
        )

include_directories(include)

include_directories(${GTEST_INSTALL_LOCATION}/include)
link_directories(${GTEST_INSTALL_LOCATION}/lib)

include_directories(${SFML_INSTALL_LOCATION}/include)
link_directories(${SFML_INSTALL_LOCATION}/lib)

include_directories(${SPDLOG_INSTALL_LOCATION}/include)
link_directories(${SPDLOG_INSTALL_LOCATION}/lib)

add_subdirectory(src)
add_subdirectory(test)
