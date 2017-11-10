#include <iostream>
#include "../Engine/headers/RenderManager.h"
#include "../Engine/headers/InputManager.h"
#include "headers/Player.h"
#include "../Engine/headers/AudioManager.h"

#undef main


int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
//
//    AudioManager::Instance().InitMusicPlayer();
//    AudioManager::Instance().LoadBGM("pokemon");
//    AudioManager::Instance().PlayBGM();


    // TODO: START. this entire block is just for testing //////////////////////////////////////////////////////////////

    auto renderManager = RenderManager::GetRenderManager();
    auto inputManager = InputManager::instance();

    SDL_PumpEvents();

    renderManager->Clear();

    std::unique_ptr<MoveableObject> player{new Player("content/soldier.png", 100, 300)};
    player->draw();
    renderManager->Flip();

    SDL_Event event;

    while (true) {

        if (inputManager->hasEvent(&event)) {
            if (inputManager->isKeyDown(event)) {
                auto direction = inputManager->getDirection(event);
                renderManager->Clear();
                player->move(direction);
                player->draw();
                renderManager->Flip();
            }

            if (event.type == SDL_QUIT) {
                break;
            }
        }
    }


    // TODO: END. this entire block is just for testing ////////////////////////////////////////////////////////////////


    std::cin.get();

    return 0;

}

