#include "CreditsState.h"
#include "../Engine/UIText.h"

CreditsState::CreditsState()
{

}

CreditsState::~CreditsState()
{
}

void CreditsState::HandleEvents(Game & game, Event& ev)
{
	auto& inputManager = InputManager::Instance();
	
	if (inputManager.IsQuit(ev))
		game.Quit();
	if (inputManager.IsMouseClicked(ev))
	{
		// Check clicks on button
		for (auto& button : _buttons)
		{
			if (button->IsClicked(ev)) button->Click();
		}
	}	
}

void CreditsState::Update(Game & game, float time)
{
}

void CreditsState::Draw(Game & game)
{
	RenderManager::Instance().DrawTexture(_background->GetTexture(), NULL, NULL);
	_miniBackground->Draw();

	// Draw all buttons
	for (auto& button : _buttons)
	{
		button->Draw();
	}

	for (auto& t : _texts)
		t.Draw();
}

void CreditsState::Init(Game& game)
{
	_background = AssetManager::Instance().LoadTexture("menu-wallpaper");
	_buttons.emplace_back(std::make_unique<Button>("button_back", Point((config::width / 2) - 150, 800), Point(300, 50), [&]() {
		// Can only delete myself from outside
		// Set clears all states and sets a states
		game.SetState(std::make_unique<MenuState>());
	}));

	_miniBackground = std::make_unique<UIIcon>(UIIcon("zwartkader", { config::width / 2 - 270, config::height / 3 - 180 }, 150));
	_texts.push_back({ "THIS GAME IS CREATED BY:", 40, {config::width / 2 - 250, config::height / 3 - 170} });
	_texts.push_back({ "Niels Kop", 40, { config::width / 2 - 250, config::height / 3 - 90 } });
	_texts.push_back({ "Sander Mol", 40, { config::width / 2 - 250, config::height / 3 - 10 } });
	_texts.push_back({ "Mevlut Özdemir", 40,{ config::width / 2 - 250, config::height / 3 + 80 } });
	_texts.push_back({ "Ahmad Rahimi", 40,{ config::width / 2 - 250, config::height / 3 + 170 } });
	_texts.push_back({ "Jarric van Krieken", 40,{ config::width / 2 - 250, config::height / 3 + 260 } });
}