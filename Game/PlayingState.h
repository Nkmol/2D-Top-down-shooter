#pragma once
#include "State.h"
#include "MoveableObject.h"
#include <memory>
#include <InputManager.h>
#include "Player.h"

class PlayingState : public State
{
public:
	PlayingState();
	~PlayingState();

	void HandleEvents(Game& game) override;
	void Update(Game& game, int time) override;
	void Draw(Game& game) override;
	void Init() override;
private:
	// Todo might actually need to be GameObject
	// Use Pointer so Slicing will not occur
	std::vector<unique_ptr<MoveableObject>> _objs;
	Player* _player;
	InputManager *inputManager;
};

