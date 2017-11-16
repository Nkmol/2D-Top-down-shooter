#include <iostream>
#include "RenderManager.h"
#include "InputManager.h"
#include "Player.h"
#include "AudioManager.h"

//#include "vld.h"
#include "TMXManager.h"
#include <memory>
#include <algorithm>


#undef main
int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

	auto& renderManager = RenderManager::Instance();
	renderManager.CreateWindow("Shooter game", false, 1500, 960);
//
//    AudioManager::Instance().InitMusicPlayer();
//    AudioManager::Instance().LoadBGM("pokemon");
//    AudioManager::Instance().PlayBGM();

	TMXManager::Instance().Init("../content/map/tilemapje2.tmx");
	TMXManager::Instance().Render();
	std::cin.get();

    // TODO: START. this entire block is just for testing //////////////////////////////////////////////////////////////

    auto inputManager = InputManager::instance();

    SDL_PumpEvents();

    std::unique_ptr<MoveableObject> player{new Player("../content/soldier.png", 100, 300)};
    player->draw();
    renderManager.Flip();

    SDL_Event event{};

    int FPS = 100;
    int MAX_FRAME_TIME = 5 * 1000 / FPS;
    int LAST_UPDATE_TIME = SDL_GetTicks();

    while (true) {

        if (inputManager.hasEvent(&event)) {

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

            if (inputManager.isKeyUp(event)) {
                player->stopMove();
            }


            if (inputManager.isQuit(event)) {
                break;
            }
        }

        // todo, alle draw functies naar rendermanager: functie: void DrawObject(MoveableObject object);
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        int time = std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME);

        player->update(time);

        LAST_UPDATE_TIME = CURRENT_TIME_MS;


        renderManager.Clear();
        player->draw();
        renderManager.Flip();
    }


    // TODO: END. this entire block is just for testing ////////////////////////////////////////////////////////////////


    return 0;

}
