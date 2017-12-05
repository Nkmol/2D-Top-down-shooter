#include "Game.h"
#include "PlayingState.h"

#undef main
int main(int argc, char *argv[]) {

    Game game;

	auto state = make_unique<PlayingState>();
    game.Init();
    game.ChangeState(std::move(state));
	
	game.Run(60);


    return 0;
}
