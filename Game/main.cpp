#include <iostream>
#include "RenderManager.h"
#include "InputManager.h"
#include "Game.h"
#include "PlayingState.h"
#include <algorithm>
#include "PausedState.h"
#include <vld.h>

#undef main

int main(int argc, char *argv[]) {

    Game game;

	auto state = make_unique<PlayingState>();
    game.Init();
    game.ChangeState(std::move(state));
	
	game.Run(60);


    return 0;

}
