#include "MenuState.h"
#include "InputManager.h"
#include "PlayingState.h"
#include "AudioManager.h"
#include "Game.h"
#include "MenuMainState.h"

MenuState::MenuState()
{ 
}
MenuState::~MenuState()
{

}

void MenuState::HandleEvents(Game& game)
{
	auto& inputManager = InputManager::Instance();
	Event ev;
	while (inputManager.HasEvent(&ev)) {
		if (inputManager.IsQuit(ev))
			game.Quit();
		else if (inputManager.IsMouseClicked(ev))
		{
			if (ev.GetEventValue().button.x > _quitButton.getX1() && ev.GetEventValue().button.x < _quitButton.getX2() && ev.GetEventValue().button.y > _quitButton.getY1() && ev.GetEventValue().button.y < _quitButton.getY2()) {
				game.Quit();
			}
			else if (ev.GetEventValue().button.x > _muteButton.getX1() && ev.GetEventValue().button.x < _muteButton.getX2() && ev.GetEventValue().button.y > _muteButton.getY1() && ev.GetEventValue().button.y < _muteButton.getY2())
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
		_subStates.back()->HandleEvents(game, *this, ev);
	}
}

void MenuState::Update(Game& game, float time)
{
	_subStates.back()->Update(game, time);
}

void MenuState::Draw(Game& game)
{
	RenderManager::Instance().DrawTexture(_background->GetTexture(), NULL, NULL);

	_muteButton.drawButton();
	_quitButton.drawButton();

	_subStates.back()->Draw();
}

void MenuState::Init()
{	
	_subStates.push_back(make_unique<MenuMainState>());
	_muteButton = Button(_muteString, config::width - 100, config::height - 100, 75, 75);
	_quitButton = Button(_quitString, (config::width / 2) - 123, (config::height / 3) * 2, 225, 45);
	_background = std::make_unique<Texture>(AssetManager::Instance().LoadTexture("menu-wallpaper"));

	int muted = 0;

	_subStates.back()->Init();
}

void MenuState::ChangeState(std::unique_ptr<MenuSubState> substate)
{
	_subStates.push_back(std::move(substate));
	_subStates.back()->Init();
}
