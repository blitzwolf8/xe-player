cmake_minimum_required(VERSION 3.14)

project(xe-player VERSION ${XE_PLAYER_VERSION} LANGUAGES CXX)

set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

include_directories(
  ${RESOURCE_DIR}
  ${INCLUDE_DIR}
  ${SOURCE_DIR}
)


set(PROJECT_SOURCES
  ${SOURCE_DIR}/main.cc
  ${SOURCE_DIR}/model.cc
  ${SOURCE_DIR}/controls.cc
  ${SOURCE_DIR}/window.cc
  ${SOURCE_DIR}/media.cc
  ${SOURCE_DIR}/view.cc
  ${SOURCE_DIR}/format.cc
  ${SOURCE_DIR}/player.cc
  ${INCLUDE_DIR}/format.h
  ${INCLUDE_DIR}/media.h
  ${INCLUDE_DIR}/view.h
  ${INCLUDE_DIR}/window.h
  ${INCLUDE_DIR}/model.h
  ${INCLUDE_DIR}/controls.h
  ${INCLUDE_DIR}/player.h
)


set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${RESOURCE_DIR})
 SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -ltag")

qt_add_executable(player
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${RESOURCE_DIR}/resource.qrc
)

set_target_properties(player
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  VERSION ${XE_PLAYER_VERSION}
)

target_include_directories(player PUBLIC ${XE_INCLUDE_DIRS})
target_link_directories(player PUBLIC ${XE_INCLUDE_DIRS})

target_compile_definitions(player
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

if(CMAKE_BUILD_TYPE STREQUAL "Asan")  
  target_compile_options(player PRIVATE -fsanitize=address )
  target_link_options(player PRIVATE -fsanitize=address )
endif(CMAKE_BUILD_TYPE STREQUAL "Asan")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(player PRIVATE -g)
  target_link_options(player PRIVATE -g )
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


target_link_libraries(player PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia )

set_target_properties(player PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER xe.xio.org
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(player)
endif()
