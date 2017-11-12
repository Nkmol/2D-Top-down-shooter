#include <iostream>
#include "../Engine/headers/RenderManager.h"
#include "../Engine/headers/InputManager.h"
#include "headers/Player.h"
#include "../Engine/headers/AudioManager.h"
#include <memory>

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

    std::unique_ptr<MoveableObject> player{new Player("content/soldier.png", 100, 300)};
    player->draw();
    renderManager->Flip();

    SDL_Event event{};

    while (true) {

        if (inputManager.hasEvent(&event)) {
            renderManager->Clear();

            // recalculate players angle to mouse ONLY IF the mouse has been moved.
            if (inputManager.isMouseMoved(event)) {
                int angle = inputManager.recalculateMouseAngle(*player);

                // setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
                player->setAngle(angle);
            }

            if (inputManager.isKeyDown(event)) {
                Direction direction = inputManager.getDirection(event);
                int angle = inputManager.calculateMouseAngle(*player);
                player->setAngle(angle);
                player->move(direction);
            }

            player->draw();
            renderManager->Flip();

            if (event.type == SDL_QUIT) {
                break;
            }
        }
    }


    // TODO: END. this entire block is just for testing ////////////////////////////////////////////////////////////////


    return 0;

}

