cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)

project(Box2D)

# Check what the project is being built on.
if(UNIX)
	set(BOX2D_INSTALL_BY_DEFAULT ON)
else(UNIX)
	set(BOX2D_INSTALL_BY_DEFAULT OFF)
endif(UNIX)

# Options for building the project.
option(BOX2D_INSTALL "Install Box2D libs, includes, and CMake scripts" ${BOX2D_INSTALL_BY_DEFAULT})
option(BOX2D_INSTALL_DOC "Install Box2D documentation" OFF)
option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" OFF)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
option(BOX2D_BUILD_EXAMPLES "Build Box2D examples" OFF)

# Set macros related to directories (where to install box2d).
set(BOX2D_VERSION 2.3.2)
set(LIB_INSTALL_DIR lib${LIB_SUFFIX})
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

# The Box2D library.
add_subdirectory(Box2D)

# Include all source files in the project directory. This is bad practice; If a source file is deleted between building, the make file won't update the project. Otherwise works fine.
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
file(GLOB main_SRC
    "*.h"
    "*.cpp"
)

# Use all source files in creating the project.
add_executable(main_test ${main_SRC})
TARGET_LINK_LIBRARIES(main_test Box2D)

# Find sfml and link it to the project.
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(main_test ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

