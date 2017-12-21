#include "PausedState.h"
#include "RenderManager.h"
#include "Config.h"
#include "Level.h"
#include "Game.h"
#include "InputManager.h"
#include "Button.h"
#include "MenuState.h"

PausedState::PausedState() {
}

PausedState::~PausedState() {
}

void PausedState::HandleEvents(Game &game, Event& event) {
    auto &inputManager = InputManager::Instance();

    if (inputManager.IsPauseResume(event)) {
        game.PopState();
    }
    if (inputManager.IsQuit(event)) {
        game.Quit();
    }
    if (inputManager.IsMousePressed(event)) {
        // Check clicks on button
        for (auto &button : _buttons) {
            if (button->IsClicked(event)) button->Click();
        }
    }
}

void PausedState::Update(Game &game, float time) {
}

void PausedState::Draw(Game &game) {
	// Draw previous state (the game)
    game.GetStateBack(1)->Draw(game);
	_UIPauseText.Draw();

    // Draw all buttons
    for (auto &button : _buttons) {
        button->draw();
    }
}

void PausedState::Init(Game &game) {
	_UIPauseText = UIText("Press ESC to resume game", 24, { config::width / 2 - 155, config::height / 2 - 20 });

	_buttons.emplace_back(
		make_unique<Button>("button_give-up", Point(config::width / 2 - 52, config::height / 4), Point(114, 40),
		                    [&]()
		                    {
			                    // Can only delete myself from outside
			                    // Set clears all states and sets a states
			                    game.PopState(2);
		                    }));
}
