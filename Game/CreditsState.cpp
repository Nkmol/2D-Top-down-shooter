#include "CreditsState.h"

CreditsState::CreditsState()
{

}

CreditsState::~CreditsState()
{
}

void CreditsState::HandleEvents(Game& game)
{
	auto& inputManager = InputManager::Instance();
	Event ev;
	while (inputManager.HasEvent(&ev)) {
		if (inputManager.IsQuit(ev))
			game.Quit();
		else if (inputManager.IsMouseClicked(ev))
		{
			if (ev.GetEventValue().button.x > _backButton.getX1() && ev.GetEventValue().button.x < _backButton.getX2() && ev.GetEventValue().button.y > _backButton.getY1() && ev.GetEventValue().button.y < _backButton.getY2()) {
				//Back to menu
				auto state = std::make_unique<MenuState>();
				game.ChangeState(std::move(state));
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
	RenderManager::Instance().DrawText("Niels Kop - ", config::width / 2 - 250, config::height / 3 - 70, 360, 40);
	RenderManager::Instance().DrawText("Sander Mol - ", config::width / 2 - 250, config::height / 3 + 30, 360, 40);
	RenderManager::Instance().DrawText("Mevlut �zdemir -", config::width / 2 - 250, config::height / 3 + 130, 360, 40);
	RenderManager::Instance().DrawText("Ahmad Rahimi -", config::width / 2 - 250, config::height / 3 + 230, 360, 40);
	RenderManager::Instance().DrawText("Jeroen Brekelmans -", config::width / 2 - 250, config::height / 3 + 330, 360, 40);

	_backButton.drawButton();
}

void CreditsState::Init()
{
	_background = std::make_unique<Texture>(AssetManager::Instance().LoadTexture("menu-wallpaper"));
	_backButton = Button("button_back", (config::width / 2) - 150, 800, 300, 50);
}
