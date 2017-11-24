#include <iostream>
#include "RenderManager.h"
#include "InputManager.h"
#include "Game.h"
#include "PlayingState.h"
#include <algorithm>

#undef main

int main(int argc, char *argv[]) {

    Game game;

    unique_ptr<PlayingState> state(new PlayingState());
    game.Init("Shooter game", false, 1280, 960);
    game.ChangeState(std::move(state));
	
	game.Run(60);


    return 0;

}
