#include "CreditsState.h"

CreditsState::CreditsState()
{

}

CreditsState::~CreditsState()
{
}

void CreditsState::HandleEvents(Game & game)
{
	auto& inputManager = InputManager::Instance();
	Event event;
	while (inputManager.HasEvent(&event)) {
		if (inputManager.IsQuit(event))
			game.Quit();
		if (inputManager.IsMouseClicked(event))
		{
			// Check clicks on button
			for (auto& button : _buttons)
			{
				if (button->IsClicked(event)) button->Click();
			}
		}
	}
}

void CreditsState::Update(Game & game, float time)
{
}

void CreditsState::Draw(Game & game)
{
	RenderManager::Instance().DrawTexture(_background->GetTexture(), NULL, NULL);
	RenderManager::Instance().DrawText("THIS GAME IS CREATED BY:", config::width / 2 - 250, config::height / 3 - 170, 360, 40);
	RenderManager::Instance().DrawText("Niels Kop", config::width / 2 - 250, config::height / 3 - 90, 360, 40);
	RenderManager::Instance().DrawText("Sander Mol", config::width / 2 - 250, config::height / 3 - 10, 360, 40);
	RenderManager::Instance().DrawText("Mevlut Ozdemir", config::width / 2 - 250, config::height / 3 + 80, 360, 40);
	RenderManager::Instance().DrawText("Ahmad Rahimi", config::width / 2 - 250, config::height / 3 + 170, 360, 40);
	RenderManager::Instance().DrawText("Jeroen Brekelmans", config::width / 2 - 250, config::height / 3 + 260, 360, 40);
	RenderManager::Instance().DrawText("Jarric van Krieken", config::width / 2 - 250, config::height / 3 + 350, 360, 40);

	// Draw all buttons
	for (auto& button : _buttons)
	{
		button->draw();
	}
}

void CreditsState::Init(Game& game)
{
	_background = AssetManager::Instance().LoadTexture("menu-wallpaper");
	_buttons.emplace_back(make_unique<Button>("button_back", Point((config::width / 2) - 150, 800), Point(300, 50), [&]() {
		// Can only delete myself from outside
		// Set clears all states and sets a states
		game.SetState(make_unique<MenuState>());
	}));
}