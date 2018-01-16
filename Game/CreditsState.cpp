#include "CreditsState.h"
#include "../Engine/UIText.h"
#include "Hud.h"

CreditsState::CreditsState()
{

}

CreditsState::~CreditsState()
{
	auto& hud = Hud::Instance();
	hud.Get<UIText>("TitelCredit")->Destroy();
	hud.Get<UIText>("Niels")->Destroy();
	hud.Get<UIText>("Sander")->Destroy();
	hud.Get<UIText>("Mevlut")->Destroy();
	hud.Get<UIText>("Ahmad")->Destroy();
	hud.Get<UIText>("Jarric")->Destroy();
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
	RenderManager::Instance().DrawTexture(_background->GetPointer(), NULL, NULL);
	_miniBackground->Draw();

	// Draw all buttons
	for (auto& button : _buttons)
	{
		button->Draw();
	}
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

	auto& hud = Hud::Instance();
	hud.AddComponent("TitelCredit", std::make_unique<UIText>(UIText{ "THIS GAME IS CREATED BY:", 40, {config::width / 2 - 250, config::height / 3 - 170} }));
	hud.AddComponent("Niels", std::make_unique<UIText>(UIText{ "Niels Kop", 40, { config::width / 2 - 250, config::height / 3 - 90 } }));
	hud.AddComponent("Sander", std::make_unique<UIText>(UIText{ "Sander Mol", 40, { config::width / 2 - 250, config::height / 3 - 10 } }));
	hud.AddComponent("Mevlut", std::make_unique<UIText>(UIText{ "Mevlut �zdemir", 40, {config::width / 2 - 250, config::height / 3 + 80} }));
	hud.AddComponent("Ahmad", std::make_unique<UIText>(UIText{ "Ahmad Rahimi", 40, {config::width / 2 - 250, config::height / 3 + 170} }));
	hud.AddComponent("Jarric", std::make_unique<UIText>(UIText{ "Jarric van Krieken", 40, {config::width / 2 - 250, config::height / 3 + 260} }));
}
