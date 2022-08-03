cmake_minimum_required(VERSION 3.14)

project(xe LANGUAGES CXX)
set(XE_VERSION 1.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})

find_package(Qt6 6.2 COMPONENTS Core Quick Gui Widgets Multimedia REQUIRED)
add_subdirectory(xe)

option(XE_BUILD_TESTS "Build all muon's tests" OFF)
mark_as_advanced(XE_BUILD_TESTS)

if(XE_BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
  add_subdirectory(tests)
endif()