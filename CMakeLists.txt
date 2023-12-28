cmake_minimum_required(VERSION 3.0.0)
project(FriedMusic++ VERSION 0.1.0 LANGUAGES C CXX)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
SET(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)


set(SOURCE_FILES main.cpp)

include_directories(lib)
link_directories(lib)

include_directories(lib/FriedMusic)
link_directories(lib/FriedMusic)

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

file(GLOB_RECURSE FriedMusicLib
     "lib/*.hpp"
     "lib/*.cpp"
)
add_library(lib ${FriedMusicLib})

include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})


add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )



target_link_libraries( ${PROJECT_NAME} lib )
target_link_libraries( ${PROJECT_NAME} cpr::cpr )

# include qt
find_package(Qt5 REQUIRED COMPONENTS Core Gui UiTools Widgets)
target_link_libraries(${PROJECT_NAME}
    Qt::Core
    Qt::Gui
    Qt::UiTools
    Qt::Widgets
)

include(CTest)
enable_testing()


# copy config file to executable (test only)
configure_file(resource/defaultConfig.json config.json COPYONLY)
file(COPY resource DESTINATION .)
