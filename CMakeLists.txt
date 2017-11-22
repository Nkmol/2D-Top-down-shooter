cmake_minimum_required(VERSION 3.8)
project(Shooter)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Shooter_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

message(${SDL2_mixer_FOUND})


include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} source/headers Engine/headers Game/headers include content)

set(SOURCE_FILES
        content
        Game/main.cpp
        Engine/AssetManager.cpp
        Engine/headers/AssetManager.h
        Engine/AudioManager.cpp
        Engine/headers/AudioManager.h
        Engine/RenderManager.cpp
        Engine/headers/RenderManager.h
        Engine/Engine.cpp
        Engine/MoveableObject.cpp
        Engine/headers/Engine.h
        Game/Game.cpp
        Game/Game.h
        Game/PlayingState.cpp
        Game/PlayingState.h
        Game/State.h
        Engine/CollidableObject.cpp
        Engine/MapManager.cpp
        Engine/headers/CollidableObject.h
        Engine/headers/MapManager.h
        Engine/tmx/include/rapidxml/rapidxml.hpp
        Engine/tmx/include/rapidxml/rapidxml_iterators.hpp
        Engine/tmx/include/rapidxml/rapidxml_print.hpp
        Engine/tmx/include/rapidxml/rapidxml_utils.hpp
        Engine/tmx/include/TMXParser.h
        Engine/tmx/include/TSXParser.h
        Engine/tmx/src/TMXParser.cpp
        Engine/tmx/src/TSXParser.cpp
        Engine/InputManager.cpp Engine/headers/InputManager.h Game/Player.cpp Game/headers/Player.h Engine/MoveableObject.cpp Engine/headers/MoveableObject.h Engine/headers/Direction.h Engine/MoveableObject.cpp
        Game/headers/Helper.h
        Engine/InputManager.cpp Engine/headers/InputManager.h Game/Player.cpp Game/headers/Player.h Engine/MoveableObject.cpp Engine/headers/MoveableObject.h Engine/headers/Direction.h Engine/MoveableObject.cpp Game/EnemyBase.cpp Game/headers/EnemyBase.h Game/FlockController.cpp Game/headers/FlockController.h Game/Flock.cpp Game/headers/Flock.h Engine/Point.cpp Engine/headers/Point.h Game/Helper.cpp Game/headers/Helper.h)
add_executable(GroepH ${SOURCE_FILES})

target_link_libraries(GroepH ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})