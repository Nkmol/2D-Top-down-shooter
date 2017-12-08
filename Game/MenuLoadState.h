#pragma once
#include "MenuSubState.h"
#include <vector>

class State;
class MenuLoadState : public MenuSubState
{
	std::vector<const char*> _saveFiles;
public:
	MenuLoadState();
	~MenuLoadState();

	void HandleEvents(Game& game, MenuState& state,Event& ev) override;
	void Update(Game& game, float time) override;
	void Draw() override;
	void Init() override;
};