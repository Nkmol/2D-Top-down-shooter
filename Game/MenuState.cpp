#include "MenuState.h"
#include "InputManager.h"
#include "PlayingState.h"
#include "AudioManager.h"
#include "Game.h"
#include <experimental/filesystem>
#include "nfd.h"
#include <json.hpp>
#include <regex>

namespace fs = std::experimental::filesystem;

MenuState::MenuState() {
    AudioManager::Instance().InitMusicPlayer();
    AudioManager::Instance().LoadBGM("mainmenu");
}

MenuState::~MenuState() {
    RenderManager::Instance().Clear();
}

void MenuState::HandleEvents(Game &game, Event& ev) {
    auto &inputManager = InputManager::Instance();

	if (inputManager.IsQuit(ev)) {
		game.Quit();
		return;
	}

	if (!inputManager.IsMouseClicked(ev)) {
		return;
	}

	if (this->IsButtonClicked(ev, _newgameButton)) {
		return;
	}

	if (this->IsButtonClicked(ev, _loadgameButton)) {
		this->LoadGame();
		return;
	}

	if (IsButtonClicked(ev, _creditsButton)) {
		auto state = std::make_unique<CreditsState>();
		game.ChangeState(std::move(state));
		return;
	}

	if (IsButtonClicked(ev, _instructions)) {
		auto state = std::make_unique<InstructionsState>();
		game.ChangeState(std::move(state));
		return;
	}

	if (IsButtonClicked(ev, _quitButton)) {
		game.Quit();
		return;
	}

	if (IsButtonClicked(ev, _muteButton)) {
		AudioManager::Instance().PauseResumeBGM();
		return;
	}

	if (IsButtonClicked(ev, _level1)) {
		if (_highestLevel >= 1) {
			StartLevel(1, game);
		}
	}
	else if (IsButtonClicked(ev, _level1)) {
		if (_highestLevel >= 2)
			StartLevel(2, game);
	}
	else if (IsButtonClicked(ev, _level1)) {
		if (_highestLevel >= 3)
		StartLevel(3, game);
	}


}



bool MenuState::IsButtonClicked(Event ev, Button button) {
	return ev.GetEventValue().button.x > button.getX1() &&
		ev.GetEventValue().button.x < button.getX2() &&
		ev.GetEventValue().button.y > button.getY1() &&
		ev.GetEventValue().button.y < button.getY2();
}

void MenuState::LoadGame() {
	fs::path path{ fs::current_path().parent_path() };

	path += "\\content\\saves";
	std::string str = path.string();

	nfdchar_t *outPath = NULL;
	nfdresult_t result = NFD_OpenDialog("json", str.c_str(), &outPath);
	if (result == NFD_OKAY) {
		//std::regex r("\.json$");
		//if (!std::regex_match(outPath, r)) return;

		_savedGame = outPath;

		free(outPath);
		std::ifstream i;
		i.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			i.open(_savedGame);
		}
		catch (const ifstream::failure &) {
			cout << "Exception opening/reading file" << endl;
			return;
		}
		nlohmann::json j;
		i >> j;

		_highestLevel = j.at("highestLevel").get<int>();
	}
	else if (result == NFD_CANCEL) {
		puts("User pressed cancel.");
	}
	else {
		printf("Error: %s\n", NFD_GetError());
	}
}

void MenuState::Update(Game &game, float time) {

}

void MenuState::Draw(Game &game) {
    RenderManager::Instance().DrawTexture(_background->GetTexture(), NULL, NULL);
	for (auto button : _allButtons) {
		button.Draw();		
	}

    if (_highestLevel >= 1)
        _level1.Draw();
    if (_highestLevel >= 2)
        _level2.Draw();
    if (_highestLevel >= 3)
        _level3.Draw();
}


void MenuState::Init(Game &game) {
    _background = AssetManager::Instance().LoadTexture("menu-wallpaper");
    _newgameButton = Button("button_new", (config::width / 2) - 150, 200, 300, 50);
    _loadgameButton = Button("button_load", (config::width / 2) - 150, 300, 300, 50);
    _creditsButton = Button("button_credits", (config::width / 2) - 150, 400, 300, 50);
    _instructions = Button("button_instructions", (config::width / 2) - 150, 500, 300, 50);
    _quitButton = Button("button_quit", (config::width / 2) - 150, 600, 300, 50);


    _level1 = Button("button_level1", 50, 200, 300, 50);
    _level2 = Button("button_level2", 50, 300, 300, 50);
    _level3 = Button("button_level3", 50, 400, 300, 50);

    _muteButton = Button("button_mute", (config::width) - 100, (config::height) - 100, 75, 75);

	_advertisementsLinks.push_back({ "advertisement/ad1", "https://nl.wikipedia.org/wiki/Canada" });
	_advertisementsLinks.push_back({ "advertisement/ad2", "https://marktplaats.nl" });
	_advertisementsLinks.push_back({ "advertisement/ad3", "https://google.nl" });



	srand(time(0));
	_adnr = rand() % _advertisementsLinks.size();
	SetRandomAd();

	_allButtons = { _newgameButton, _loadgameButton, _creditsButton, _muteButton, _quitButton, _instructions, _advertisement };

    int muted = 0;
}


void MenuState::StartLevel(const int level, Game &game) {
    auto state = std::make_unique<PlayingState>(level, _savedGame);
    game.ChangeState(std::move(state));
    AudioManager::Instance().StopBGM();
}

void MenuState::SetRandomAd() {
	_advertisement = Button(_advertisementsLinks.at(_adnr).at(0), Point(config::width / 6, config::height * 0.9), Point(config::width / 6 * 4, config::height * 0.1), [&]() {
		auto temp = "start " + _advertisementsLinks.at(_adnr).at(1);
		char *cstr = new char[temp.length() + 1];
		strcpy(cstr, temp.c_str());
		system(cstr);
		delete[] cstr;
	});
	
}
