#include "MenuState.h"
#include "InputManager.h"
#include "PlayingState.h"
#include "AudioManager.h"
#include "Game.h"
#include <experimental/filesystem>
#include <nfd.h>
#include <memory>

namespace fs = std::experimental::filesystem;

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
			if (ev.GetEventValue().button.x > _newgameButton.getX1() && ev.GetEventValue().button.x < _newgameButton.getX2() && ev.GetEventValue().button.y > _newgameButton.getY1() && ev.GetEventValue().button.y < _newgameButton.getY2()) {
				//New game
				auto state = std::make_unique<PlayingState>();
				game.ChangeState(std::move(state));
				AudioManager::Instance().StopBGM();
				game.SetLevel(1);
				// todo, alle draw functies naar rendermanager: functie: void DrawObject(MoveableObject object);
			}

			else if (ev.GetEventValue().button.x > _loadgameButton.getX1() && ev.GetEventValue().button.x < _loadgameButton.getX2() && ev.GetEventValue().button.y > _loadgameButton.getY1() && ev.GetEventValue().button.y < _loadgameButton.getY2()) {
				std::string savedGame;

				fs::path path{ fs::current_path().parent_path() };

				path += "\\content\\saves";
				std::wstring ws(path);
				std::string str(ws.begin(), ws.end());

				nfdchar_t *outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("json", str.c_str(), &outPath);
				if (result == NFD_OKAY)
				{
					savedGame = outPath;
					free(outPath);

				}
				else if (result == NFD_CANCEL)
				{
					puts("User pressed cancel.");
				}
				else
				{
					printf("Error: %s\n", NFD_GetError());
				}
			}

			else if (ev.GetEventValue().button.x > _creditsButton.getX1() && ev.GetEventValue().button.x < _creditsButton.getX2() && ev.GetEventValue().button.y > _creditsButton.getY1() && ev.GetEventValue().button.y < _creditsButton.getY2()) {
				//Credits
			}
			else if (ev.GetEventValue().button.x > _quitButton.getX1() && ev.GetEventValue().button.x < _quitButton.getX2() && ev.GetEventValue().button.y > _quitButton.getY1() && ev.GetEventValue().button.y < _quitButton.getY2()) {
				game.Quit();
			}
			else if (ev.GetEventValue().button.x > _muteButton.getX1() && ev.GetEventValue().button.x < _muteButton.getX2() && ev.GetEventValue().button.y > _muteButton.getY1() && ev.GetEventValue().button.y < _muteButton.getY2())
			{
				//Mute
				if (_muted == 1) {
					AudioManager::Instance().StopBGM();
					RenderManager::Instance().Clear();
					_muted = 0;
				}
				else {
					AudioManager::Instance().InitMusicPlayer();
					AudioManager::Instance().LoadBGM("mainmenu");
					AudioManager::Instance().PlayBGM();
					_muted = 1;
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
	RenderManager::Instance().DrawTexture(_background->GetTexture(), NULL, NULL);

	_newgameButton.drawButton();
	_loadgameButton.drawButton();
	_creditsButton.drawButton();
	_muteButton.drawButton();
	_quitButton.drawButton();
}

void MenuState::Init()
{
	_background = std::make_unique<Texture>(AssetManager::Instance().LoadTexture("menu-wallpaper"));

	_newgameButton = Button(_newgameString, (config::width / 2) - 123, (config::height / 3) * 0.5, 225, 45);
	_loadgameButton = Button(_loadgameString, (config::width / 2) - 123, (config::height / 3) * 1, 225, 45);
	_creditsButton = Button(_creditsString, (config::width / 2) - 123, (config::height / 3) * 1.5, 225, 45);
	_muteButton = Button(_muteString, (config::width / 2) + 200, (config::height / 3) * 2, 75, 75);
	_quitButton = Button(_quitString, (config::width / 2) - 123, (config::height / 3) * 2, 225, 45);

	int muted = 0;
}