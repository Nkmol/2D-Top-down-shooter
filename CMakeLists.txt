cmake_minimum_required(VERSION 3.8)
project(Shooter)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Shooter_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-narrowing")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(json REQUIRED)
find_package(SDL2_ttf REQUIRED)

message(${SDL2_mixer_FOUND})


include_directories(${SDL2_TTF_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} source/headers Engine/headers Game/headers include content bin/include)

set(SOURCE_FILES
        Game/MenuState.cpp
        Game/AIBat.h
        Game/PlayingState.cpp
        Game/EnemyBase.cpp
        Game/Handgun.cpp
        Game/FlockController.cpp
        Game/AIDefault.h
        Game/Player.cpp
        Game/PlayingState.h
        Game/AIDefault.cpp
        Game/Config.h
        Game/Shotgun.cpp
        Game/Shotgun.h
        Game/Wave.cpp
        Game/WaveController.cpp
        Game/Level.cpp
        Game/AIBat.cpp
        Game/Weapon.cpp
        Game/Helper.cpp
        Game/PausedState.h
        Game/IAIBase.h
        Game/Level.h
        Game/Game.h
        Game/Flock.cpp
        Game/PausedState.cpp
        Game/MenuState.h
        Game/WaveController.h
        Game/Handgun.h
        Game/Wave.h
        Game/Bullet.cpp
        Game/State.h
        Game/Uzi.cpp
        Game/main.cpp
        Game/FactoryBehaviour.h
        Game/Game.cpp
        Game/headers/Helper.h
        Game/headers/Player.h
        Game/headers/Flock.h
        Game/headers/Weapon.h
        Game/headers/Bullet.h
        Game/headers/FlockController.h
        Game/headers/Uzi.h
        Game/headers/EnemyBase.h
        Engine/Button.cpp
        Engine/MoveableObject.cpp
        Engine/CustomDeleter.h
        Engine/TickerTime.cpp
        Engine/GameObject.cpp
        Engine/RenderManager.cpp
        Engine/PhysicsManager.cpp
        Engine/InputManager.cpp
        Engine/Point.cpp
        Engine/AssetManager.cpp
        Engine/Button.h
        Engine/MapManager.cpp
        Engine/Engine.cpp
        Engine/QuadTree.cpp
        Engine/QuadTree.h
        Engine/AudioManager.cpp
        Engine/headers/RenderManager.h
        Engine/headers/Engine.h
        Engine/headers/MapManager.h
        Engine/headers/InputManager.h
        Engine/headers/GameObject.h
        Engine/headers/AudioManager.h
        Engine/headers/Point.h
        Engine/headers/Event.h
        Engine/headers/AssetManager.h
        Engine/headers/PhysicsManager.h
        Engine/headers/MoveableObject.h
        Engine/headers/TickerTime.h
        Engine/tmx/include/TMXParser.h
        Engine/tmx/include/TSXParser.h
        Engine/tmx/src/TMXParser.cpp
        Engine/tmx/src/TSXParser.cpp Engine/AnimationManager.cpp Engine/AnimationManager.h)
add_executable(Shooter ${SOURCE_FILES})

target_link_libraries(Shooter ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})