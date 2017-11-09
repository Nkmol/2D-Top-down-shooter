#include <iostream>
#include "../Engine/Engine.h"
#include "../Engine/RenderManager.h"
#include "../Engine/headers/InputManager.h"
#include "headers/Player.h"
//#include "AudioManager.h"

#undef main

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    auto engine = new Engine::MainManager();

    auto inputManager = InputManager::instance();

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *_window;
    SDL_Renderer *_renderer;

    SDL_CreateWindowAndRenderer(1080, 720, 0, &_window, &_renderer);
    SDL_SetWindowTitle(_window, "Shooter");
    SDL_Surface *surface = SDL_GetWindowSurface(_window);


    SDL_Event event;

    std::unique_ptr<Player> player{new Player};
    player->setXPos(0);
    player->setYPos(0);


    while (true) {

        if (inputManager->hasEvent(&event)) {
            if (inputManager->isKeyDown(event)) {
                auto direction = inputManager->getKey(event);
                player->move(direction);

                std::cout << "X: " << player->getXPos() << std::endl;
                std::cout << "Y: " << player->getYPos() << std::endl << std::endl;
            }

            if (event.type == SDL_QUIT) {
                break;
            }
        }
    }


    std::cout << engine->Message;

    std::cin.get();

    return 0;
}