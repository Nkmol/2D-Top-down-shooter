cmake_minimum_required(VERSION 3.8)
project(Shooter)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Shooter_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

message(${SDL2_mixer_FOUND})


include_directories(${SDL2_TTF_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} source/headers Engine/headers Game/headers include content)

set(SOURCE_FILES
        content
        Engine/headers
        Engine/tmx
        Engine/MoveableObject.cpp
        Engine/TickerTime.cpp
        Engine/GameObject.cpp
        Engine/RenderManager.cpp
        Engine/PhysicsManager.cpp
        Engine/InputManager.cpp
        Engine/Point.cpp
        Engine/AssetManager.cpp
        Engine/MapManager.cpp
        Engine/Engine.cpp
        Engine/AudioManager.cpp
        Engine/headers/RenderManager.h
        Engine/headers/Engine.h
        Engine/headers/MapManager.h
        Engine/headers/InputManager.h
        Engine/headers/GameObject.h
        Engine/headers/AudioManager.h
        Engine/headers/Point.h
        Engine/headers/AssetManager.h
        Engine/headers/PhysicsManager.h
        Engine/headers/MoveableObject.h
        Engine/headers/TickerTime.h
        Engine/tmx/include
        Engine/tmx/src
        Engine/tmx/include/rapidxml
        Engine/tmx/include/TMXParser.h
        Engine/tmx/include/TSXParser.h
        Engine/tmx/src/TMXParser.cpp
        Engine/tmx/src/TSXParser.cpp
        Game/headers
        Game/PlayingState.cpp
        Game/EnemyBase.cpp
        Game/FlockController.cpp
        Game/Player.cpp
        Game/PlayingState.h
        Game/Config.h
        Game/Weapon.cpp
        Game/Helper.cpp
        Game/PausedState.h
        Game/Game.h
        Game/Flock.cpp
        Game/PausedState.cpp
        Game/Bullet.cpp
        Game/State.h
        Game/Uzi.cpp
        Game/main.cpp
        Game/Game.cpp
        Game/headers/Helper.h
        Game/headers/Player.h
        Game/headers/Flock.h
        Game/headers/Weapon.h
        Game/headers/Bullet.h
        Game/headers/FlockController.h
        Game/headers/Uzi.h
        Game/headers/EnemyBase.h
        Game/Level.cpp
        Game/Level.h
        Game/monsters/ZombieEnemy.cpp Game/monsters/ZombieEnemy.h Game/monsters/BatEnemy.cpp Game/monsters/BatEnemy.h
        Game/Handgun.cpp Game/Handgun.h Game/Shotgun.cpp Game/Shotgun.h)
add_executable(GroepH ${SOURCE_FILES})

target_link_libraries(GroepH ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})