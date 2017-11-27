#include "MenuState.h"
#include "Player.h"
#include "InputManager.h"
#include <memory>
#include "PlayingState.h"
#include <algorithm>
#include "MapManager.h"
#include "Audiomanager.h"

MenuState::MenuState()
{
}
MenuState::~MenuState()
{

}

void MenuState::HandleEvents(Game& game)
{
	auto inputManager = InputManager::instance();
	SDL_Event ev;
	if (inputManager.hasEvent(&ev)) {
		if (inputManager.isQuit(ev))
			game.Quit();
		else if (inputManager.isMouseDown(ev))
		{
			if (ev.button.x > newgamebutton.getX1() && ev.button.x < newgamebutton.getX2() && ev.button.y > newgamebutton.getY1() && ev.button.y < newgamebutton.getY2()) {
				//New game
				//SDL_RenderClear(this->renderer);
				unique_ptr<PlayingState> state(new PlayingState());
				game.ChangeState(std::move(state));
				AudioManager::Instance().StopBGM();
				MapManager::Instance().Init("../content/map/halflife.tmx");
				// todo, alle draw functies naar rendermanager: functie: void DrawObject(MoveableObject object);
			}

			else if (ev.button.x > SCREEN_WIDTH / 3 && ev.button.x < (SCREEN_WIDTH / 3 + 225) && ev.button.y >(SCREEN_HEIGHT / 3) * 1.25 && ev.button.y < ((SCREEN_HEIGHT / 3) * 1.25 + 45)) {
				//Load game
			}

			else if (ev.button.x > SCREEN_WIDTH / 3 && ev.button.x < (SCREEN_WIDTH / 3 + 225) && ev.button.y >(SCREEN_HEIGHT / 3) * 1.75 && ev.button.y < ((SCREEN_HEIGHT / 3) * 1.75 + 45)) {
				//Credits
			}
		}
	}
}

void MenuState::Update(Game& game, float time)
{

}

void MenuState::Draw(Game& game)
{
	RenderManager::Instance().DrawButton(SCREEN_WIDTH, SCREEN_HEIGHT, newgamebutton.getX1(), newgamebutton.getY1(), "newgamebutton");
	RenderManager::Instance().DrawButton(SCREEN_WIDTH, SCREEN_HEIGHT, loadgamebutton.getX1(), loadgamebutton.getY1(), "loadgamebutton");
	RenderManager::Instance().DrawButton(SCREEN_WIDTH, SCREEN_HEIGHT, creditsbutton.getX1(), creditsbutton.getY1(), "creditsbutton");

}

void MenuState::Init()
{
	newgamebutton = Button(SCREEN_WIDTH / 3, (SCREEN_HEIGHT / 3) * 0.75, 225, 45);
	loadgamebutton = Button(SCREEN_WIDTH / 3, (SCREEN_HEIGHT / 3) * 1.25, 225, 45);
	creditsbutton = Button(SCREEN_WIDTH / 3, (SCREEN_HEIGHT / 3) * 1.75, 225, 45);

	AudioManager::Instance().InitMusicPlayer();
	AudioManager::Instance().LoadBGM("mainmenu");
	AudioManager::Instance().PlayBGM();

	//auto* player = new Player("../content/soldier.png", 100, 300);
	//_objs.emplace_back(player);

	// save pointer seperate
	//_player = player;
}
