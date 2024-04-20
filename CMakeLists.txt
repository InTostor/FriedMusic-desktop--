cmake_minimum_required(VERSION 3.0.0)
project(FriedMusic++ VERSION 0.1.0 LANGUAGES C CXX)
# SET(CMAKE_CXX_FLAGS "-O3 -Os -mavx2 -mbmi2 -march=native -Ofast -frename-registers -fopenmp")
SET(CXX_STANDARD 17)


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeChecksCache)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
SET(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)

# Get the current working branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)


add_definitions(-DGIT_COMMIT_HASH=${GIT_COMMIT_HASH})
add_definitions(-DGIT_BRANCH=${GIT_BRANCH})
# configure_file(
#   ${CMAKE_SOURCE_DIR}/lib/FriedMusic/version.h
#   ${CMAKE_BINARY_DIR}/generated/version.h
# )
include_directories(${CMAKE_BINARY_DIR}/generated)

    

# Include CPR library as
include(FetchContent)
FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  # https://github.com/libcpr/cpr/releases
  GIT_TAG 1.10.5)
FetchContent_MakeAvailable(cpr)


# For finding Qt includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})


# include SQLiteCpp
link_directories(${PROJECT_NAME} "lib/sqlite_modern_cpp")
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)

file(GLOB SOURCES 
"lib/FriedMusic/*.cpp"
# "lib/FriedMusic/*.hpp"
# "lib/FriedMusic/*.h"
)
set (SOURCES ${SOURCES} "main.cpp")
include_directories(${PROJECT_SOURCE_DIR}/lib/FriedMusic)

add_executable( ${PROJECT_NAME} ${SOURCES})

# target_link_libraries( ${PROJECT_NAME} SOURCES )
target_link_libraries( ${PROJECT_NAME} cpr::cpr )
target_link_libraries(${PROJECT_NAME} 
SQLiteCpp
sqlite3
pthread
dl
)

# include qt
find_package(Qt5 REQUIRED COMPONENTS Core Gui UiTools Widgets Multimedia Concurrent)
target_link_libraries(${PROJECT_NAME}
    Qt::Core
    Qt::Gui
    Qt::UiTools
    Qt::Widgets
    Qt::Multimedia
    Qt::Concurrent
)

#include json
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)


include(CTest)
enable_testing()


# copy config file to executable (test only)
configure_file(resource/defaultConfig.json config.json COPYONLY)
file(COPY resource DESTINATION .)
