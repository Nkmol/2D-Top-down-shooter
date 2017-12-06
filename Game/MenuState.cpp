#include "MenuState.h"
#include "InputManager.h"
#include "PlayingState.h"
#include "AudioManager.h"
#include "Game.h"


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

			else if (ev.button.x > loadgamebutton.getX1() && ev.button.x < loadgamebutton.getX2() && ev.button.y > loadgamebutton.getY1() && ev.button.y < loadgamebutton.getY2()) {
				//Load game
			}

			else if (ev.button.x > creditsbutton.getX1() && ev.button.x < creditsbutton.getX2() && ev.button.y > creditsbutton.getY1() && ev.button.y < creditsbutton.getY2()) {
				//Credits
			}
			else if (ev.button.x > quitbutton.getX1() && ev.button.x < quitbutton.getX2() && ev.button.y > quitbutton.getY1() && ev.button.y < quitbutton.getY2()) {
				game.Quit();
			}
			else if (ev.button.x > mutebutton.getX1() && ev.button.x < mutebutton.getX2() && ev.button.y > mutebutton.getY1() && ev.button.y < mutebutton.getY2())
			{
				//Mute
				if (muted == 1) {
					AudioManager::Instance().StopBGM();
					RenderManager::Instance().Clear();
					muted = 0;
				}
				else {
					AudioManager::Instance().InitMusicPlayer();
					AudioManager::Instance().LoadBGM("mainmenu");
					AudioManager::Instance().PlayBGM();
					muted = 1;
				}
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
	mutebutton.drawButton();
	quitbutton.drawButton();
}

void MenuState::Init()
{
	newgamebutton = Button(newgameString, (SCREEN_WIDTH / 2) - 123, (SCREEN_HEIGHT / 3) * 0.5, 225, 45);
	loadgamebutton = Button(loadgameString, (SCREEN_WIDTH / 2) - 123, (SCREEN_HEIGHT / 3) * 1, 225, 45);
	creditsbutton = Button(creditsString, (SCREEN_WIDTH / 2) - 123, (SCREEN_HEIGHT / 3) * 1.5, 225, 45);
	mutebutton = Button(muteString, (SCREEN_WIDTH / 2) + 200, (SCREEN_HEIGHT / 3) * 2, 75, 75);
	quitbutton = Button(quitString, (SCREEN_WIDTH / 2) - 123, (SCREEN_HEIGHT / 3) * 2, 225, 45);

	int muted = 0;
}
