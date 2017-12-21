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

void MenuState::HandleEvents(Game &game) {
    auto &inputManager = InputManager::Instance();
    Event ev;

    while (inputManager.HasEvent(&ev)) {

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

        if (ev.GetEventValue().button.x > _level1.getX1() && ev.GetEventValue().button.x < _level1.getX2() &&
            ev.GetEventValue().button.y > _level1.getY1() && ev.GetEventValue().button.y < _level1.getY2()) {
            if (_highestLevel >= 1) {
                StartLevel(1, game);
            }
        } else if (ev.GetEventValue().button.x > _level2.getX1() && ev.GetEventValue().button.x < _level2.getX2() &&
                   ev.GetEventValue().button.y > _level2.getY1() && ev.GetEventValue().button.y < _level2.getY2()) {
            if (_highestLevel >= 2)
                StartLevel(2, game);
        } else if (ev.GetEventValue().button.x > _level3.getX1() && ev.GetEventValue().button.x < _level3.getX2() &&
                   ev.GetEventValue().button.y > _level3.getY1() && ev.GetEventValue().button.y < _level3.getY2()) {
            //if (_highestLevel >= 3)
            //StartLevel(3, game);
        }
    }
}


bool MenuState::IsButtonClicked(Event ev, Button button) {
    return ev.GetEventValue().button.x > button.getX1() &&
           ev.GetEventValue().button.x < button.getX2() &&
           ev.GetEventValue().button.y > button.getY1() &&
           ev.GetEventValue().button.y < button.getY2();
}

void MenuState::LoadGame() {
    fs::path path{fs::current_path().parent_path()};

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
    } else if (result == NFD_CANCEL) {
        puts("User pressed cancel.");
    } else {
        printf("Error: %s\n", NFD_GetError());
    }
}

void MenuState::Update(Game &game, float time) {

}

void MenuState::Draw(Game &game) {
    RenderManager::Instance().DrawTexture(_background->GetTexture(), NULL, NULL);

    Button allButtons[] = {_newgameButton, _loadgameButton, _creditsButton, _muteButton, _quitButton, _instructions};

    for (auto button : allButtons) {
        button.draw();
    }

    if (_highestLevel >= 1)
        _level1.draw();
    if (_highestLevel >= 2)
        _level2.draw();
    if (_highestLevel >= 3)
        _level3.draw();
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

    int muted = 0;
}


void MenuState::StartLevel(const int level, Game &game) {
    auto state = std::make_unique<PlayingState>(level, _savedGame);
    game.ChangeState(std::move(state));
    AudioManager::Instance().StopBGM();
}