#include <iostream>
#include "RenderManager.h"
#include "InputManager.h"
#include "Player.h"
#include "AudioManager.h"

//#include "vld.h"
#include <memory>
#include <algorithm>
//<<<<<<< HEAD
#include "Game.h"
#include "PlayingState.h"

//=======
//#include <Uzi.h>
//>>>>>>> bullet

#undef main

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

	//auto& renderManager = RenderManager::Instance();
//
//    AudioManager::Instance().InitMusicPlayer();
//    AudioManager::Instance().LoadBGM("pokemon");
//    AudioManager::Instance().PlayBGM();

	Game game;

    unique_ptr<PlayingState> state(new PlayingState());
    game.Init("Shooter game", false, 1500, 960);
    game.ChangeState(state.get());

//<<<<<<< HEAD
//
//    // TODO: START. this entire block is just for testing //////////////////////////////////////////////////////////////
//=======
////    auto &renderManager = RenderManager::Instance();
////    renderManager.CreateWindow("Shooter game", false, 1500, 960);
//>>>>>>> bullet

    auto inputManager = InputManager::instance();

    //SDL_PumpEvents();

//<<<<<<< HEAD
//=======
//    std::unique_ptr<Weapon> uzi{new Uzi()};
//
//    std::unique_ptr<Player> player{new Player("../content/soldier.png", 100, 300)};
//    player->addWeapon(*uzi);
//    player->draw();
//
//    renderManager.Flip();
//>>>>>>> bullet

   /* SDL_Event event{};*/

    int FPS = 100;
    int MAX_FRAME_TIME = 5 * 1000 / FPS;
    int LAST_UPDATE_TIME = SDL_GetTicks();

//<<<<<<< HEAD
    bool isPlaying = true;

    while (isPlaying) {

        //if (inputManager.hasEvent(&event)) {

        //    // recalculate players angle to mouse ONLY IF the mouse has been moved.
        //    if (inputManager.isMouseMoved(event)) {
        //        int angle = inputManager.recalculateMouseAngle(*player);

        //        // setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
        //        player->setAngle(angle);
        //    }   

        //    if (inputManager.isKeyDown(event)) {
        //        Direction direction = inputManager.getDirection(event);
        //        int angle = inputManager.calculateMouseAngle(*player);
        //        player->setAngle(angle);
        //        player->move(direction);
        //    }

        //    if (inputManager.isKeyUp(event)) {
        //        player->stopMove();
        //    }


        //    if (inputManager.isQuit(event)) {
        //        break;
        //    }
        //}
//=======
//    while (true) {
//        if (inputManager.hasEvent(&event)) {
//
//            // recalculate players angle to mouse ONLY IF the mouse has been moved.
//            if (inputManager.isMouseMoved(event)) {
//                int angle = inputManager.recalculateMouseAngle(*player);
//                angle = (angle + 360) % 360;
//                std::cout << angle << std::endl;
//
//                // setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
//                player->setAngle(angle);
//            }
//
//            if (inputManager.isKeyDown(event)) {
//                Direction direction = inputManager.getDirection(event);
//                int angle = inputManager.calculateMouseAngle(*player);
//                angle = (angle + 360) % 360;
//                player->setAngle(angle);
//                player->move(direction);
//            }
//
//            if (inputManager.isMouseClicked(event)) {
//                player->shoot();
//            }
//
//            if (inputManager.isKeyUp(event)) {
//                player->stopMove();
//            }
//
//            if (inputManager.isQuit(event)) {
//                break;
//            }
//        }
//>>>>>>> bullet

        // todo, alle draw functies naar rendermanager: functie: void DrawObject(MoveableObject object);
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        int time = std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME);


		game.HandleEvents();
		game.Update(time);
        //player->update(time);


        LAST_UPDATE_TIME = CURRENT_TIME_MS;

		game.Draw();
       /* renderManager.Clear();
        player->draw();
<<<<<<< HEAD
        renderManager.Flip();*/
//=======
//        player->getWeapon().drawBullets();
//        renderManager.Flip();
//>>>>>>> bullet
    }


    // TODO: END. this entire block is just for testing ////////////////////////////////////////////////////////////////


    return 0;

}
