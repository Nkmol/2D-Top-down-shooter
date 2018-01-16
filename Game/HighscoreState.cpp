#include "HighscoreState.h"
#include "MenuState.h"
#include "Hud.h"


HighscoreState::HighscoreState()
{
}


HighscoreState::~HighscoreState()
{
	auto& hud = Hud::Instance();
	auto i = 0;
	for (auto && highscore : _highscores)
	{
		hud.Get<UIText>(&"H"[i])->Destroy();
		i++;
	}
	//hud.Get<UIText>("Titel")->Destroy();
	//hud.Get<UIText>("Moving")->Destroy();
	//hud.Get<UIText>("Aiming")->Destroy();
	//hud.Get<UIText>("Shooting")->Destroy();
	//hud.Get<UIText>("Pause")->Destroy();
	//hud.Get<UIText>("Cheats")->Destroy();
	//hud.Get<UIText>("Speed")->Destroy();
}

void HighscoreState::Init(Game& game)
{
	auto j = AssetManager::Instance().LoadJson("highscores.json");
	if(!j.is_null())
	{
		_highscores = j.get<decltype(_highscores)>();
	}

	_background = AssetManager::Instance().LoadTexture("menu-wallpaper");
	_buttons.emplace_back(make_unique<Button>("button_back", Point((config::width / 2) - 150, 800), Point(300, 50), [&]() {
		// Can only delete myself from outside
		// Set clears all states and sets a states
		game.SetState(make_unique<MenuState>());
	}));

	_miniBackground = std::make_unique<UIIcon>(UIIcon("zwartkader", { config::width / 2 - 270, config::height / 3 - 180 }, 150));
	auto& hud = Hud::Instance();
	auto i = 0;
	for (auto && highscore : _highscores)
	{
		hud.AddComponent(std::string(&"H" [ i]), make_unique<UIText>(UIText{ std::string(highscore.first) + " - " + std::string(highscore.second), 25,{ config::width / 2 - 180, config::height / 3 - 100 + 50.f*i } }));
		i++;
	}
	//hud.AddComponent("Titel", make_unique<UIText>(UIText{ "Controls: ", 25,{ config::width / 2 - 120, config::height / 3 - 100 } }));
	//hud.AddComponent("Moving", make_unique<UIText>(UIText{ "Moving: W, A, S & D ", 25,{ config::width / 2 - 120, config::height / 3 - 50 } }));
	//hud.AddComponent("Aiming", make_unique<UIText>(UIText{ "Aiming: Mouse move", 25,{ config::width / 2 - 120, config::height / 3 - 0 } }));
	//hud.AddComponent("Shooting", make_unique<UIText>(UIText{ "Shooting: LMB, Reload: R", 25,{ config::width / 2 - 120, config::height / 3 + 50 } }));
	//hud.AddComponent("Pause", make_unique<UIText>(UIText{ "Pause: Esc Button", 25,{ config::width / 2 - 120, config::height / 3 + 100 } }));
	//hud.AddComponent("Cheats", make_unique<UIText>(UIText{ "Cheats: K & N", 25, {config::width / 2 - 120, config::height / 3 + 150} }));
	//hud.AddComponent("Speed", make_unique<UIText>(UIText{ "Change level speed: [ & ]", 25, {config::width / 2 - 120, config::height / 3 + 200} }));
}

void HighscoreState::HandleEvents(Game & game, Event & event)
{
	auto& inputManager = InputManager::Instance();
	
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

void HighscoreState::Update(Game & game, float time)
{
}

void HighscoreState::Draw(Game & game)
{
	RenderManager::Instance().DrawTexture(_background->GetPointer(), NULL, NULL);

	_miniBackground->Draw();

	// Draw all buttons
	for (auto& button : _buttons)
	{
		button->Draw();
	}
}
