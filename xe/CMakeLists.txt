cmake_minimum_required(VERSION 3.14)

project(xe VERSION ${XE_VERSION} LANGUAGES CXX)

set(RESOURCE_DIR "${xe_SOURCE_DIR}/res")
set(INCLUDE_DIR "${xe_SOURCE_DIR}/include")
set(SOURCE_DIR "${xe_SOURCE_DIR}/src")

include_directories(
  ${RESOURCE_DIR}
  ${INCLUDE_DIR}
  ${SOURCE_DIR}
)


file(GLOB_RECURSE XE_SOURCES
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cc"
)

add_library(xe STATIC ${XE_SOURCES} )

target_link_libraries(xe PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)

target_compile_definitions(xe PRIVATE XE_LIBRARY)


file(GLOB_RECURSE SOURCES
    "${RESOURCE_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cc"
)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${RESOURCE_DIR})

qt_add_executable(xe-main
    MANUAL_FINALIZATION
    xe_main.cc
    res/resource.qrc
)

target_include_directories(xe-main PUBLIC ${XE_INCLUDE_DIRS})
target_link_directories(xe-main PUBLIC ${XE_INCLUDE_DIRS})

target_compile_definitions(xe-main
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

if(CMAKE_BUILD_TYPE STREQUAL "Asan")  
  target_compile_options(xe-main PRIVATE -fsanitize=address -ltag)
  target_link_options(xe-main PRIVATE -fsanitize=address -ltag)
endif(CMAKE_BUILD_TYPE STREQUAL "Asan")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(xe-main PRIVATE -g -O3 -ltag)
  target_link_options(xe-main PRIVATE -g -O3 -ltag)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


if(CMAKE_BUILD_TYPE STREQUAL "Tsan")
  target_compile_options(xe-main PRIVATE -fsanitize=thread)
  target_link_options(xe-main PRIVATE -fsanitize=thread)
endif(CMAKE_BUILD_TYPE STREQUAL "Tsan")

target_link_libraries(xe-main PUBLIC xe)

set_target_properties(xe-main PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER xe.xio.org
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(xe-main)
endif()
