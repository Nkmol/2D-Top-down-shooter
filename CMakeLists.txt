cmake_minimum_required(VERSION 3.8)
project(Shooter)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Shooter_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

message(${SDL2_mixer_FOUND})


include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} source/headers include content)

set(SOURCE_FILES
        content
        Game/main.cpp
        Engine/AssetManager.cpp
        Engine/AssetManager.h
        Engine/AudioManager.cpp
        Engine/AudioManager.h
        Engine/RenderManager.cpp
        Engine/RenderManager.h
        Engine/Engine.cpp
        Engine/Engine.h
        )
add_executable(GroepH ${SOURCE_FILES})

target_link_libraries(GroepH ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})