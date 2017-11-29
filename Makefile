# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/MevlutOzdemir/Developers/project/GroepH

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/MevlutOzdemir/Developers/project/GroepH

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/MevlutOzdemir/Developers/project/GroepH/CMakeFiles /Users/MevlutOzdemir/Developers/project/GroepH/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/MevlutOzdemir/Developers/project/GroepH/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named GroepH

# Build rule for target.
GroepH: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 GroepH
.PHONY : GroepH

# fast build rule for target.
GroepH/fast:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/build
.PHONY : GroepH/fast

Engine/AssetManager.o: Engine/AssetManager.cpp.o

.PHONY : Engine/AssetManager.o

# target to build an object file
Engine/AssetManager.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/AssetManager.cpp.o
.PHONY : Engine/AssetManager.cpp.o

Engine/AssetManager.i: Engine/AssetManager.cpp.i

.PHONY : Engine/AssetManager.i

# target to preprocess a source file
Engine/AssetManager.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/AssetManager.cpp.i
.PHONY : Engine/AssetManager.cpp.i

Engine/AssetManager.s: Engine/AssetManager.cpp.s

.PHONY : Engine/AssetManager.s

# target to generate assembly for a file
Engine/AssetManager.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/AssetManager.cpp.s
.PHONY : Engine/AssetManager.cpp.s

Engine/AudioManager.o: Engine/AudioManager.cpp.o

.PHONY : Engine/AudioManager.o

# target to build an object file
Engine/AudioManager.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/AudioManager.cpp.o
.PHONY : Engine/AudioManager.cpp.o

Engine/AudioManager.i: Engine/AudioManager.cpp.i

.PHONY : Engine/AudioManager.i

# target to preprocess a source file
Engine/AudioManager.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/AudioManager.cpp.i
.PHONY : Engine/AudioManager.cpp.i

Engine/AudioManager.s: Engine/AudioManager.cpp.s

.PHONY : Engine/AudioManager.s

# target to generate assembly for a file
Engine/AudioManager.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/AudioManager.cpp.s
.PHONY : Engine/AudioManager.cpp.s

Engine/Engine.o: Engine/Engine.cpp.o

.PHONY : Engine/Engine.o

# target to build an object file
Engine/Engine.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/Engine.cpp.o
.PHONY : Engine/Engine.cpp.o

Engine/Engine.i: Engine/Engine.cpp.i

.PHONY : Engine/Engine.i

# target to preprocess a source file
Engine/Engine.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/Engine.cpp.i
.PHONY : Engine/Engine.cpp.i

Engine/Engine.s: Engine/Engine.cpp.s

.PHONY : Engine/Engine.s

# target to generate assembly for a file
Engine/Engine.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/Engine.cpp.s
.PHONY : Engine/Engine.cpp.s

Engine/GameObject.o: Engine/GameObject.cpp.o

.PHONY : Engine/GameObject.o

# target to build an object file
Engine/GameObject.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/GameObject.cpp.o
.PHONY : Engine/GameObject.cpp.o

Engine/GameObject.i: Engine/GameObject.cpp.i

.PHONY : Engine/GameObject.i

# target to preprocess a source file
Engine/GameObject.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/GameObject.cpp.i
.PHONY : Engine/GameObject.cpp.i

Engine/GameObject.s: Engine/GameObject.cpp.s

.PHONY : Engine/GameObject.s

# target to generate assembly for a file
Engine/GameObject.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/GameObject.cpp.s
.PHONY : Engine/GameObject.cpp.s

Engine/InputManager.o: Engine/InputManager.cpp.o

.PHONY : Engine/InputManager.o

# target to build an object file
Engine/InputManager.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/InputManager.cpp.o
.PHONY : Engine/InputManager.cpp.o

Engine/InputManager.i: Engine/InputManager.cpp.i

.PHONY : Engine/InputManager.i

# target to preprocess a source file
Engine/InputManager.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/InputManager.cpp.i
.PHONY : Engine/InputManager.cpp.i

Engine/InputManager.s: Engine/InputManager.cpp.s

.PHONY : Engine/InputManager.s

# target to generate assembly for a file
Engine/InputManager.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/InputManager.cpp.s
.PHONY : Engine/InputManager.cpp.s

Engine/MapManager.o: Engine/MapManager.cpp.o

.PHONY : Engine/MapManager.o

# target to build an object file
Engine/MapManager.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/MapManager.cpp.o
.PHONY : Engine/MapManager.cpp.o

Engine/MapManager.i: Engine/MapManager.cpp.i

.PHONY : Engine/MapManager.i

# target to preprocess a source file
Engine/MapManager.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/MapManager.cpp.i
.PHONY : Engine/MapManager.cpp.i

Engine/MapManager.s: Engine/MapManager.cpp.s

.PHONY : Engine/MapManager.s

# target to generate assembly for a file
Engine/MapManager.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/MapManager.cpp.s
.PHONY : Engine/MapManager.cpp.s

Engine/MoveableObject.o: Engine/MoveableObject.cpp.o

.PHONY : Engine/MoveableObject.o

# target to build an object file
Engine/MoveableObject.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/MoveableObject.cpp.o
.PHONY : Engine/MoveableObject.cpp.o

Engine/MoveableObject.i: Engine/MoveableObject.cpp.i

.PHONY : Engine/MoveableObject.i

# target to preprocess a source file
Engine/MoveableObject.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/MoveableObject.cpp.i
.PHONY : Engine/MoveableObject.cpp.i

Engine/MoveableObject.s: Engine/MoveableObject.cpp.s

.PHONY : Engine/MoveableObject.s

# target to generate assembly for a file
Engine/MoveableObject.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/MoveableObject.cpp.s
.PHONY : Engine/MoveableObject.cpp.s

Engine/PhysicsManager.o: Engine/PhysicsManager.cpp.o

.PHONY : Engine/PhysicsManager.o

# target to build an object file
Engine/PhysicsManager.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/PhysicsManager.cpp.o
.PHONY : Engine/PhysicsManager.cpp.o

Engine/PhysicsManager.i: Engine/PhysicsManager.cpp.i

.PHONY : Engine/PhysicsManager.i

# target to preprocess a source file
Engine/PhysicsManager.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/PhysicsManager.cpp.i
.PHONY : Engine/PhysicsManager.cpp.i

Engine/PhysicsManager.s: Engine/PhysicsManager.cpp.s

.PHONY : Engine/PhysicsManager.s

# target to generate assembly for a file
Engine/PhysicsManager.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/PhysicsManager.cpp.s
.PHONY : Engine/PhysicsManager.cpp.s

Engine/Point.o: Engine/Point.cpp.o

.PHONY : Engine/Point.o

# target to build an object file
Engine/Point.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/Point.cpp.o
.PHONY : Engine/Point.cpp.o

Engine/Point.i: Engine/Point.cpp.i

.PHONY : Engine/Point.i

# target to preprocess a source file
Engine/Point.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/Point.cpp.i
.PHONY : Engine/Point.cpp.i

Engine/Point.s: Engine/Point.cpp.s

.PHONY : Engine/Point.s

# target to generate assembly for a file
Engine/Point.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/Point.cpp.s
.PHONY : Engine/Point.cpp.s

Engine/RenderManager.o: Engine/RenderManager.cpp.o

.PHONY : Engine/RenderManager.o

# target to build an object file
Engine/RenderManager.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/RenderManager.cpp.o
.PHONY : Engine/RenderManager.cpp.o

Engine/RenderManager.i: Engine/RenderManager.cpp.i

.PHONY : Engine/RenderManager.i

# target to preprocess a source file
Engine/RenderManager.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/RenderManager.cpp.i
.PHONY : Engine/RenderManager.cpp.i

Engine/RenderManager.s: Engine/RenderManager.cpp.s

.PHONY : Engine/RenderManager.s

# target to generate assembly for a file
Engine/RenderManager.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/RenderManager.cpp.s
.PHONY : Engine/RenderManager.cpp.s

Engine/TickerTime.o: Engine/TickerTime.cpp.o

.PHONY : Engine/TickerTime.o

# target to build an object file
Engine/TickerTime.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/TickerTime.cpp.o
.PHONY : Engine/TickerTime.cpp.o

Engine/TickerTime.i: Engine/TickerTime.cpp.i

.PHONY : Engine/TickerTime.i

# target to preprocess a source file
Engine/TickerTime.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/TickerTime.cpp.i
.PHONY : Engine/TickerTime.cpp.i

Engine/TickerTime.s: Engine/TickerTime.cpp.s

.PHONY : Engine/TickerTime.s

# target to generate assembly for a file
Engine/TickerTime.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/TickerTime.cpp.s
.PHONY : Engine/TickerTime.cpp.s

Engine/tmx/src/TMXParser.o: Engine/tmx/src/TMXParser.cpp.o

.PHONY : Engine/tmx/src/TMXParser.o

# target to build an object file
Engine/tmx/src/TMXParser.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/tmx/src/TMXParser.cpp.o
.PHONY : Engine/tmx/src/TMXParser.cpp.o

Engine/tmx/src/TMXParser.i: Engine/tmx/src/TMXParser.cpp.i

.PHONY : Engine/tmx/src/TMXParser.i

# target to preprocess a source file
Engine/tmx/src/TMXParser.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/tmx/src/TMXParser.cpp.i
.PHONY : Engine/tmx/src/TMXParser.cpp.i

Engine/tmx/src/TMXParser.s: Engine/tmx/src/TMXParser.cpp.s

.PHONY : Engine/tmx/src/TMXParser.s

# target to generate assembly for a file
Engine/tmx/src/TMXParser.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/tmx/src/TMXParser.cpp.s
.PHONY : Engine/tmx/src/TMXParser.cpp.s

Engine/tmx/src/TSXParser.o: Engine/tmx/src/TSXParser.cpp.o

.PHONY : Engine/tmx/src/TSXParser.o

# target to build an object file
Engine/tmx/src/TSXParser.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/tmx/src/TSXParser.cpp.o
.PHONY : Engine/tmx/src/TSXParser.cpp.o

Engine/tmx/src/TSXParser.i: Engine/tmx/src/TSXParser.cpp.i

.PHONY : Engine/tmx/src/TSXParser.i

# target to preprocess a source file
Engine/tmx/src/TSXParser.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/tmx/src/TSXParser.cpp.i
.PHONY : Engine/tmx/src/TSXParser.cpp.i

Engine/tmx/src/TSXParser.s: Engine/tmx/src/TSXParser.cpp.s

.PHONY : Engine/tmx/src/TSXParser.s

# target to generate assembly for a file
Engine/tmx/src/TSXParser.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Engine/tmx/src/TSXParser.cpp.s
.PHONY : Engine/tmx/src/TSXParser.cpp.s

Game/Bullet.o: Game/Bullet.cpp.o

.PHONY : Game/Bullet.o

# target to build an object file
Game/Bullet.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Bullet.cpp.o
.PHONY : Game/Bullet.cpp.o

Game/Bullet.i: Game/Bullet.cpp.i

.PHONY : Game/Bullet.i

# target to preprocess a source file
Game/Bullet.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Bullet.cpp.i
.PHONY : Game/Bullet.cpp.i

Game/Bullet.s: Game/Bullet.cpp.s

.PHONY : Game/Bullet.s

# target to generate assembly for a file
Game/Bullet.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Bullet.cpp.s
.PHONY : Game/Bullet.cpp.s

Game/EnemyBase.o: Game/EnemyBase.cpp.o

.PHONY : Game/EnemyBase.o

# target to build an object file
Game/EnemyBase.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/EnemyBase.cpp.o
.PHONY : Game/EnemyBase.cpp.o

Game/EnemyBase.i: Game/EnemyBase.cpp.i

.PHONY : Game/EnemyBase.i

# target to preprocess a source file
Game/EnemyBase.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/EnemyBase.cpp.i
.PHONY : Game/EnemyBase.cpp.i

Game/EnemyBase.s: Game/EnemyBase.cpp.s

.PHONY : Game/EnemyBase.s

# target to generate assembly for a file
Game/EnemyBase.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/EnemyBase.cpp.s
.PHONY : Game/EnemyBase.cpp.s

Game/Flock.o: Game/Flock.cpp.o

.PHONY : Game/Flock.o

# target to build an object file
Game/Flock.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Flock.cpp.o
.PHONY : Game/Flock.cpp.o

Game/Flock.i: Game/Flock.cpp.i

.PHONY : Game/Flock.i

# target to preprocess a source file
Game/Flock.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Flock.cpp.i
.PHONY : Game/Flock.cpp.i

Game/Flock.s: Game/Flock.cpp.s

.PHONY : Game/Flock.s

# target to generate assembly for a file
Game/Flock.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Flock.cpp.s
.PHONY : Game/Flock.cpp.s

Game/FlockController.o: Game/FlockController.cpp.o

.PHONY : Game/FlockController.o

# target to build an object file
Game/FlockController.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/FlockController.cpp.o
.PHONY : Game/FlockController.cpp.o

Game/FlockController.i: Game/FlockController.cpp.i

.PHONY : Game/FlockController.i

# target to preprocess a source file
Game/FlockController.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/FlockController.cpp.i
.PHONY : Game/FlockController.cpp.i

Game/FlockController.s: Game/FlockController.cpp.s

.PHONY : Game/FlockController.s

# target to generate assembly for a file
Game/FlockController.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/FlockController.cpp.s
.PHONY : Game/FlockController.cpp.s

Game/Game.o: Game/Game.cpp.o

.PHONY : Game/Game.o

# target to build an object file
Game/Game.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Game.cpp.o
.PHONY : Game/Game.cpp.o

Game/Game.i: Game/Game.cpp.i

.PHONY : Game/Game.i

# target to preprocess a source file
Game/Game.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Game.cpp.i
.PHONY : Game/Game.cpp.i

Game/Game.s: Game/Game.cpp.s

.PHONY : Game/Game.s

# target to generate assembly for a file
Game/Game.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Game.cpp.s
.PHONY : Game/Game.cpp.s

Game/Handgun.o: Game/Handgun.cpp.o

.PHONY : Game/Handgun.o

# target to build an object file
Game/Handgun.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Handgun.cpp.o
.PHONY : Game/Handgun.cpp.o

Game/Handgun.i: Game/Handgun.cpp.i

.PHONY : Game/Handgun.i

# target to preprocess a source file
Game/Handgun.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Handgun.cpp.i
.PHONY : Game/Handgun.cpp.i

Game/Handgun.s: Game/Handgun.cpp.s

.PHONY : Game/Handgun.s

# target to generate assembly for a file
Game/Handgun.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Handgun.cpp.s
.PHONY : Game/Handgun.cpp.s

Game/Helper.o: Game/Helper.cpp.o

.PHONY : Game/Helper.o

# target to build an object file
Game/Helper.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Helper.cpp.o
.PHONY : Game/Helper.cpp.o

Game/Helper.i: Game/Helper.cpp.i

.PHONY : Game/Helper.i

# target to preprocess a source file
Game/Helper.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Helper.cpp.i
.PHONY : Game/Helper.cpp.i

Game/Helper.s: Game/Helper.cpp.s

.PHONY : Game/Helper.s

# target to generate assembly for a file
Game/Helper.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Helper.cpp.s
.PHONY : Game/Helper.cpp.s

Game/Level.o: Game/Level.cpp.o

.PHONY : Game/Level.o

# target to build an object file
Game/Level.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Level.cpp.o
.PHONY : Game/Level.cpp.o

Game/Level.i: Game/Level.cpp.i

.PHONY : Game/Level.i

# target to preprocess a source file
Game/Level.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Level.cpp.i
.PHONY : Game/Level.cpp.i

Game/Level.s: Game/Level.cpp.s

.PHONY : Game/Level.s

# target to generate assembly for a file
Game/Level.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Level.cpp.s
.PHONY : Game/Level.cpp.s

Game/PausedState.o: Game/PausedState.cpp.o

.PHONY : Game/PausedState.o

# target to build an object file
Game/PausedState.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/PausedState.cpp.o
.PHONY : Game/PausedState.cpp.o

Game/PausedState.i: Game/PausedState.cpp.i

.PHONY : Game/PausedState.i

# target to preprocess a source file
Game/PausedState.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/PausedState.cpp.i
.PHONY : Game/PausedState.cpp.i

Game/PausedState.s: Game/PausedState.cpp.s

.PHONY : Game/PausedState.s

# target to generate assembly for a file
Game/PausedState.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/PausedState.cpp.s
.PHONY : Game/PausedState.cpp.s

Game/Player.o: Game/Player.cpp.o

.PHONY : Game/Player.o

# target to build an object file
Game/Player.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Player.cpp.o
.PHONY : Game/Player.cpp.o

Game/Player.i: Game/Player.cpp.i

.PHONY : Game/Player.i

# target to preprocess a source file
Game/Player.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Player.cpp.i
.PHONY : Game/Player.cpp.i

Game/Player.s: Game/Player.cpp.s

.PHONY : Game/Player.s

# target to generate assembly for a file
Game/Player.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Player.cpp.s
.PHONY : Game/Player.cpp.s

Game/PlayingState.o: Game/PlayingState.cpp.o

.PHONY : Game/PlayingState.o

# target to build an object file
Game/PlayingState.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/PlayingState.cpp.o
.PHONY : Game/PlayingState.cpp.o

Game/PlayingState.i: Game/PlayingState.cpp.i

.PHONY : Game/PlayingState.i

# target to preprocess a source file
Game/PlayingState.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/PlayingState.cpp.i
.PHONY : Game/PlayingState.cpp.i

Game/PlayingState.s: Game/PlayingState.cpp.s

.PHONY : Game/PlayingState.s

# target to generate assembly for a file
Game/PlayingState.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/PlayingState.cpp.s
.PHONY : Game/PlayingState.cpp.s

Game/Shotgun.o: Game/Shotgun.cpp.o

.PHONY : Game/Shotgun.o

# target to build an object file
Game/Shotgun.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Shotgun.cpp.o
.PHONY : Game/Shotgun.cpp.o

Game/Shotgun.i: Game/Shotgun.cpp.i

.PHONY : Game/Shotgun.i

# target to preprocess a source file
Game/Shotgun.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Shotgun.cpp.i
.PHONY : Game/Shotgun.cpp.i

Game/Shotgun.s: Game/Shotgun.cpp.s

.PHONY : Game/Shotgun.s

# target to generate assembly for a file
Game/Shotgun.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Shotgun.cpp.s
.PHONY : Game/Shotgun.cpp.s

Game/Uzi.o: Game/Uzi.cpp.o

.PHONY : Game/Uzi.o

# target to build an object file
Game/Uzi.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Uzi.cpp.o
.PHONY : Game/Uzi.cpp.o

Game/Uzi.i: Game/Uzi.cpp.i

.PHONY : Game/Uzi.i

# target to preprocess a source file
Game/Uzi.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Uzi.cpp.i
.PHONY : Game/Uzi.cpp.i

Game/Uzi.s: Game/Uzi.cpp.s

.PHONY : Game/Uzi.s

# target to generate assembly for a file
Game/Uzi.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Uzi.cpp.s
.PHONY : Game/Uzi.cpp.s

Game/Weapon.o: Game/Weapon.cpp.o

.PHONY : Game/Weapon.o

# target to build an object file
Game/Weapon.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Weapon.cpp.o
.PHONY : Game/Weapon.cpp.o

Game/Weapon.i: Game/Weapon.cpp.i

.PHONY : Game/Weapon.i

# target to preprocess a source file
Game/Weapon.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Weapon.cpp.i
.PHONY : Game/Weapon.cpp.i

Game/Weapon.s: Game/Weapon.cpp.s

.PHONY : Game/Weapon.s

# target to generate assembly for a file
Game/Weapon.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/Weapon.cpp.s
.PHONY : Game/Weapon.cpp.s

Game/main.o: Game/main.cpp.o

.PHONY : Game/main.o

# target to build an object file
Game/main.cpp.o:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/main.cpp.o
.PHONY : Game/main.cpp.o

Game/main.i: Game/main.cpp.i

.PHONY : Game/main.i

# target to preprocess a source file
Game/main.cpp.i:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/main.cpp.i
.PHONY : Game/main.cpp.i

Game/main.s: Game/main.cpp.s

.PHONY : Game/main.s

# target to generate assembly for a file
Game/main.cpp.s:
	$(MAKE) -f CMakeFiles/GroepH.dir/build.make CMakeFiles/GroepH.dir/Game/main.cpp.s
.PHONY : Game/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... GroepH"
	@echo "... Engine/AssetManager.o"
	@echo "... Engine/AssetManager.i"
	@echo "... Engine/AssetManager.s"
	@echo "... Engine/AudioManager.o"
	@echo "... Engine/AudioManager.i"
	@echo "... Engine/AudioManager.s"
	@echo "... Engine/Engine.o"
	@echo "... Engine/Engine.i"
	@echo "... Engine/Engine.s"
	@echo "... Engine/GameObject.o"
	@echo "... Engine/GameObject.i"
	@echo "... Engine/GameObject.s"
	@echo "... Engine/InputManager.o"
	@echo "... Engine/InputManager.i"
	@echo "... Engine/InputManager.s"
	@echo "... Engine/MapManager.o"
	@echo "... Engine/MapManager.i"
	@echo "... Engine/MapManager.s"
	@echo "... Engine/MoveableObject.o"
	@echo "... Engine/MoveableObject.i"
	@echo "... Engine/MoveableObject.s"
	@echo "... Engine/PhysicsManager.o"
	@echo "... Engine/PhysicsManager.i"
	@echo "... Engine/PhysicsManager.s"
	@echo "... Engine/Point.o"
	@echo "... Engine/Point.i"
	@echo "... Engine/Point.s"
	@echo "... Engine/RenderManager.o"
	@echo "... Engine/RenderManager.i"
	@echo "... Engine/RenderManager.s"
	@echo "... Engine/TickerTime.o"
	@echo "... Engine/TickerTime.i"
	@echo "... Engine/TickerTime.s"
	@echo "... Engine/tmx/src/TMXParser.o"
	@echo "... Engine/tmx/src/TMXParser.i"
	@echo "... Engine/tmx/src/TMXParser.s"
	@echo "... Engine/tmx/src/TSXParser.o"
	@echo "... Engine/tmx/src/TSXParser.i"
	@echo "... Engine/tmx/src/TSXParser.s"
	@echo "... Game/Bullet.o"
	@echo "... Game/Bullet.i"
	@echo "... Game/Bullet.s"
	@echo "... Game/EnemyBase.o"
	@echo "... Game/EnemyBase.i"
	@echo "... Game/EnemyBase.s"
	@echo "... Game/Flock.o"
	@echo "... Game/Flock.i"
	@echo "... Game/Flock.s"
	@echo "... Game/FlockController.o"
	@echo "... Game/FlockController.i"
	@echo "... Game/FlockController.s"
	@echo "... Game/Game.o"
	@echo "... Game/Game.i"
	@echo "... Game/Game.s"
	@echo "... Game/Handgun.o"
	@echo "... Game/Handgun.i"
	@echo "... Game/Handgun.s"
	@echo "... Game/Helper.o"
	@echo "... Game/Helper.i"
	@echo "... Game/Helper.s"
	@echo "... Game/Level.o"
	@echo "... Game/Level.i"
	@echo "... Game/Level.s"
	@echo "... Game/PausedState.o"
	@echo "... Game/PausedState.i"
	@echo "... Game/PausedState.s"
	@echo "... Game/Player.o"
	@echo "... Game/Player.i"
	@echo "... Game/Player.s"
	@echo "... Game/PlayingState.o"
	@echo "... Game/PlayingState.i"
	@echo "... Game/PlayingState.s"
	@echo "... Game/Shotgun.o"
	@echo "... Game/Shotgun.i"
	@echo "... Game/Shotgun.s"
	@echo "... Game/Uzi.o"
	@echo "... Game/Uzi.i"
	@echo "... Game/Uzi.s"
	@echo "... Game/Weapon.o"
	@echo "... Game/Weapon.i"
	@echo "... Game/Weapon.s"
	@echo "... Game/main.o"
	@echo "... Game/main.i"
	@echo "... Game/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

