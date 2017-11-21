#include <iostream>
#include "RenderManager.h"
#include "InputManager.h"
#include "Player.h"
#include "AudioManager.h"

//#include "vld.h"
#include <memory>
#include <algorithm>
#include "Game.h"
#include "Menu.h"
#include "PlayingState.h"
#include "InputManager.h"
#include "Button.h"

void Menu::DrawMenu()
{

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	auto inputManager = InputManager::instance();
	auto& renderManager = RenderManager::Instance();
	renderManager.CreateWindow("Shooter game", false, SCREEN_WIDTH, SCREEN_HEIGHT);

	renderManager.AddMenuSurfaces(SCREEN_WIDTH, SCREEN_HEIGHT);

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			// Getting the quit and the keyboard events
			if (inputManager.isQuit(ev))
				isRunning = false;
			else if (inputManager.isMouseDown(ev))
			{
				Button newgamebutton(SCREEN_WIDTH / 3, (SCREEN_HEIGHT / 3) * 0.75, 225, 45);
				if (ev.button.x > newgamebutton.getX1() && ev.button.x < newgamebutton.getX2() && ev.button.y > newgamebutton.getY1() && ev.button.y < newgamebutton.getY2()) {
					//New game
					//SDL_RenderClear(this->renderer);
					isRunning = false;
					renderManager.Clear();
					Game game;

					unique_ptr<PlayingState> state(new PlayingState());
					game.Init("Shooter game", false, 1500, 960);
					game.ChangeState(state.get());

					// TODO: START. this entire block is just for testing //////////////////////////////////////////////////////////////


					//SDL_PumpEvents();

					//std::unique_ptr<MoveableObject> player{new Player("../content/soldier.png", 100, 300)};
					//player->draw();
					//renderManager.Flip();

					/* SDL_Event event{};*/

					int FPS = 100;
					int MAX_FRAME_TIME = 5 * 1000 / FPS;
					int LAST_UPDATE_TIME = SDL_GetTicks();

					while (true) {

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
						renderManager.Flip();*/
					}

				}

				else if (ev.button.x > SCREEN_WIDTH / 3 && ev.button.x < (SCREEN_WIDTH / 3 + 225) && ev.button.y >(SCREEN_HEIGHT / 3) * 1.25 && ev.button.y < ((SCREEN_HEIGHT / 3) * 1.25 + 45)) {
					//Load game
				}

				else if (ev.button.x > SCREEN_WIDTH / 3 && ev.button.x < (SCREEN_WIDTH / 3 + 225) && ev.button.y >(SCREEN_HEIGHT / 3) * 1.75 && ev.button.y < ((SCREEN_HEIGHT / 3) * 1.75 + 45)) {
					//Credits
				}

			}
		}
		SDL_UpdateWindowSurface(renderManager.GetWindow());
	}
	SDL_DestroyWindow(renderManager.GetWindow());

	SDL_Quit();
}