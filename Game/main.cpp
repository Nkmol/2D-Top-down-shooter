#include <algorithm>
#include "Game.h"
#include "PlayingState.h"
#include "MenuState.h"
//#include <vld.h>

#undef main
int main(int argc, char *argv[]) {

    Game game;

	auto state = std::make_unique<MenuState>();
    game.Init();
    game.ChangeState(std::move(state));
	
	game.Run(60);


    return 0;
}
