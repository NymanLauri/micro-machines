cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)

project(Box2D)

if(UNIX)
	set(BOX2D_INSTALL_BY_DEFAULT ON)
else(UNIX)
	set(BOX2D_INSTALL_BY_DEFAULT OFF)
endif(UNIX)

option(BOX2D_INSTALL "Install Box2D libs, includes, and CMake scripts" ${BOX2D_INSTALL_BY_DEFAULT})
option(BOX2D_INSTALL_DOC "Install Box2D documentation" OFF)
option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" OFF)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
option(BOX2D_BUILD_EXAMPLES "Build Box2D examples" OFF)

set(BOX2D_VERSION 2.3.2)
set(LIB_INSTALL_DIR lib${LIB_SUFFIX})
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

# The Box2D library.
add_subdirectory(Box2D)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
#SET(CMAKE_CXX_COMPILER "g++")
#SET(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system -I$(IDIR) -L$(LIBBOX2D_LOCATION) -lBox2D -std=c++11")
#SET(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system -I$(IDIR) -L$(LIBBOX2D_LOCATION) -std=c++11")
#include_directories("${PROJECT_SOURCE_DIR}/../lib/Box2D/Box2D") 
#add_subdirectory (${PROJECT_SOURCE_DIR}/../lib/Box2D/Box2D) 
add_executable(sfml_test sfml_test.cpp)
TARGET_LINK_LIBRARIES(sfml_test Box2D)
#set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(sfml_test ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

#find_package(SFML REQUIRED freetype-s graphics window-s system)
#include_directories(SFML_XXX_DEPENDENCIES)
#target_link_libraries (sfml_test SFML_XXX_DEPENDENCIES)
#include_directories(SFML)
#target_link_libraries (sfml_test SFML)
