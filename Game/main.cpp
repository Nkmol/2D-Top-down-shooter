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

    auto inputManager = InputManager::instance();

    int FPS = 100;
    int MAX_FRAME_TIME = 5 * 1000 / FPS;
    int LAST_UPDATE_TIME = SDL_GetTicks();

    bool isPlaying = true;

    while (isPlaying) {
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        int time = std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME);

        game.HandleEvents();
        game.Update(time);

        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        game.Draw();
    }


    // TODO: END. this entire block is just for testing ////////////////////////////////////////////////////////////////


    return 0;

}
