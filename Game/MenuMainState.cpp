#include "MenuMainState.h"
#include "InputManager.h"
#include "PlayingState.h"
#include "Game.h"
#include "AudioManager.h"
#include "Config.h"
#include "MenuState.h"
#include "MenuLoadState.h"

MenuMainState::MenuMainState()
{
}

MenuMainState::~MenuMainState()
{
}

void MenuMainState::HandleEvents(Game& game, MenuState& state, Event& ev)
{
	if (InputManager::Instance().IsMouseClicked(ev))
	{
		if (ev.GetEventValue().button.x > _newGameButton.getX1() && ev.GetEventValue().button.x < _newGameButton.getX2() && ev.GetEventValue().button.y > _newGameButton.getY1() && ev.GetEventValue().button.y < _newGameButton.getY2()) {
			//New game
			auto state = make_unique<PlayingState>();
			game.ChangeState(std::move(state));
			AudioManager::Instance().StopBGM();
			game.SetLevel(1);
		}

		else if (ev.GetEventValue().button.x > _loadGameButton.getX1() && ev.GetEventValue().button.x < _loadGameButton.getX2() && ev.GetEventValue().button.y > _loadGameButton.getY1() && ev.GetEventValue().button.y < _loadGameButton.getY2()) {
			// Load Saved
			state.ChangeState(make_unique<MenuLoadState>());
		}

		else if (ev.GetEventValue().button.x > _creditsButton.getX1() && ev.GetEventValue().button.x < _creditsButton.getX2() && ev.GetEventValue().button.y > _creditsButton.getY1() && ev.GetEventValue().button.y < _creditsButton.getY2()) {
			//Credits
		}
	}
}

void MenuMainState::Update(Game & game, float time)
{
}

void MenuMainState::Draw()
{
	_newGameButton.drawButton();
	_loadGameButton.drawButton();
	_creditsButton.drawButton();
}

void MenuMainState::Init()
{
	_newGameButton = Button(_newGameString, (config::width / 2) - 123, (config::height / 3) * 0.5, 225, 45);
	_loadGameButton = Button(_loadGameString, (config::width / 2) - 123, (config::height / 3) * 1, 225, 45);
	_creditsButton = Button(_creditsString, (config::width / 2) - 123, (config::height / 3) * 1.5, 225, 45);
}
