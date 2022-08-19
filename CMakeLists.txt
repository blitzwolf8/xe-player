cmake_minimum_required(VERSION 3.14)

project(xe-player LANGUAGES CXX)
set(XE_PLAYER_VERSION 1.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})

find_package(Qt6 6.2 COMPONENTS Core Quick Gui Widgets Multimedia Sql REQUIRED)
add_subdirectory(player)

option(XE_BUILD_TESTS "Build all xe-player's tests" OFF)
mark_as_advanced(XE_PLAYER_BUILD_TESTS)

if(XE_PLAYER_BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
  add_subdirectory(tests)
endif()