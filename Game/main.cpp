#include <iostream>
#include "RenderManager.h"
#include "InputManager.h"
#include "Player.h"
#include "AudioManager.h"
#include <memory>
#include <algorithm>

#undef main
void CreateMenu();
void PlayGame();
int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
	SDL_Surface *windowSurface = nullptr;
//    AudioManager::Instance().InitMusicPlayer();
//    AudioManager::Instance().LoadBGM("pokemon");
//    AudioManager::Instance().PlayBGM();


    // TODO: START. this entire block is just for testing //////////////////////////////////////////////////////////////
	CreateMenu();

    // TODO: END. this entire block is just for testing ////////////////////////////////////////////////////////////////


    return 0;
	//renderManager.CreateMenu();

}

void CreateMenu()
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	auto& renderManager = RenderManager::Instance();
	renderManager.CreateWindow("Shooter game", false, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Surface* windowSurface = SDL_GetWindowSurface(renderManager.GetWindow());
	SDL_Surface* image1 = AssetManager::getInstance().loadSurface("newgamebutton");
	SDL_Surface* image2 = AssetManager::getInstance().loadSurface("loadgamebutton");
	SDL_Surface* image3 = AssetManager::getInstance().loadSurface("creditbutton");

	renderManager.apply_surface(SCREEN_WIDTH / 3, (SCREEN_HEIGHT / 3) * 0.75, image1, windowSurface);
	renderManager.apply_surface(SCREEN_WIDTH / 3, (SCREEN_HEIGHT / 3) * 1.25, image2, windowSurface);
	renderManager.apply_surface(SCREEN_WIDTH / 3, (SCREEN_HEIGHT / 3) * 1.75, image3, windowSurface);

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			// Getting the quit and the keyboard events
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.x > SCREEN_WIDTH / 3 && ev.button.x < (SCREEN_WIDTH / 3 + 225) && ev.button.y >(SCREEN_HEIGHT / 3) * 0.75 && ev.button.y < ((SCREEN_HEIGHT / 3) * 0.75 + 45)) {
					//New game
					//SDL_RenderClear(this->renderer);
					SDL_DestroyWindow(renderManager.GetWindow());
					PlayGame();
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

	// Freeing the memory
	SDL_FreeSurface(image1);
	SDL_FreeSurface(image2);
	SDL_FreeSurface(image3);
	SDL_DestroyWindow(renderManager.GetWindow());

	image1 = image2 = image3 = windowSurface = nullptr;

	SDL_Quit();


}
void PlayGame() 
{
	auto& renderManager = RenderManager::Instance();
	renderManager.CreateWindow("Shooter game", false, 1500, 960);

	auto inputManager = InputManager::instance();

	SDL_PumpEvents();

	std::unique_ptr<MoveableObject> player{ new Player("../content/soldier.png", 100, 300) };
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

}