cmake_minimum_required(VERSION 3.8)
project(GroepH)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${GroepH_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(BOX2D REQUIRED)

find_path(BOX2D_INCLUDE_DIRS Box2D/include/Box2D/Box2D.h)
find_library(BOX2D_LIBRARIES Box2D/lib/libBox2D.a)
file(GLOB GroepH_SRC
        "*.h"
        "*.cpp"
        )
if(BOX2D_LIBRARIES)
    MESSAGE("BOX2D LIBRARIES FOUND")
else()
    MESSAGE("BOX2D LIBRARIES NOT FOUND")
endif()

if(BOX2D_INCLUDE_DIRS)
    MESSAGE("BOX2D DIRECTORIES FOUND")
else()
    MESSAGE("BOX2D DIRECTORIES NOT FOUND")
endif()

if(BOX2D_LIBRARY_RELEASE)
    MESSAGE("BOX2D RELEASE LIBRARY FOUND")
else()
    MESSAGE("BOX2D RELEASE LIBRARY NOT FOUND")
endif()

#SDL2 IMAGE
if(SDL2_IMAGE_LIBRARIES)
    MESSAGE("SDL2_IMAGE LIBRARY FOUND")
else()
    MESSAGE("SDL2_IMAGE LIBRARY NOT FOUND")
endif()

if(SDL2_IMAGE_INCLUDE_DIR)
    MESSAGE("SDL2_IMAGE DIRECTORIES FOUND")
else()
    MESSAGE("SDL2_IMAGE DIRECTORIES NOT FOUND")
endif()

#SDL2
if(SDL2_INCLUDE_DIR)
    MESSAGE("SDL2 DIRECTORIES FOUND")
else()
    MESSAGE("SDL2 DIRECTORIES NOT FOUND")
endif()

if(SDL2_LIBRARY)
    MESSAGE("SDL2 LIBRARY FOUND")
else()
    MESSAGE("SDL2 LIBRARY NOT FOUND")
endif()



include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${BOX2D_INCLUDE_DIR} src/game/headers src/engine/headers content include)
set(SOURCE_FILES
        content/sprites/PLACEHOLDER.txt
        src/engine/headers/rendermanager.h
        src/engine/source/rendermanager.cpp
        src/engine/headers/Engine.h
        src/engine/source/Engine.cpp
        src/engine/headers/rendermanager.h
        src/game/main.cpp
        include
        ${BOX2D_INCLUDE_DIR}
        )

add_executable(GroepH ${SOURCE_FILES} ${GroepH_SRC})

target_link_libraries(GroepH ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${BOX2D_LIBRARY_RELEASE})#${BOX2D_LIBRARY} ${BOX2D_LIBRARY_RELEASE} ${BOX2D_LIBRARY_DEBUG})