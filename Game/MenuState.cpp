#include "MenuState.h"


MenuState::MenuState()
{ 
}
MenuState::~MenuState()
{

}

void MenuState::HandleEvents(Game& game)
{
	auto& inputManager = InputManager::instance();
	SDL_Event ev;
	while (inputManager.hasEvent(&ev)) {
		if (inputManager.isQuit(ev))
			game.Quit();
		else if (inputManager.isMouseClicked(ev))
		{
			if (ev.button.x > newgamebutton.getX1() && ev.button.x < newgamebutton.getX2() && ev.button.y > newgamebutton.getY1() && ev.button.y < newgamebutton.getY2()) {
				//New game
				//SDL_RenderClear(this->renderer);
				auto state = make_unique<PlayingState>();
				game.ChangeState(std::move(state));
				AudioManager::Instance().StopBGM();
				game.SetLevel(1);
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
	newgamebutton.drawButton();
	loadgamebutton.drawButton();
	creditsbutton.drawButton();
}

void MenuState::Init()
{
	newgamebutton = Button(newgameString, (SCREEN_WIDTH / 2) - 123, (SCREEN_HEIGHT / 3) * 0.75, 225, 45);
	loadgamebutton = Button(loadgameString, (SCREEN_WIDTH / 2) - 123, (SCREEN_HEIGHT / 3) * 1.25, 225, 45);
	creditsbutton = Button(creditsString, (SCREEN_WIDTH / 2) - 123, (SCREEN_HEIGHT / 3) * 1.75, 225, 45);


	AudioManager::Instance().InitMusicPlayer();
	AudioManager::Instance().LoadBGM("mainmenu");
	AudioManager::Instance().PlayBGM();
}
