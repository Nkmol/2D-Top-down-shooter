#pragma once

#include <memory>
#include <vector>
#include "State.h"
#include "Level.h"

class Player;
class MoveableObject;

class PlayingState : public State {
public:
    PlayingState();
	PlayingState(int level, const std::string& savedGame);

	~PlayingState();

    void HandleEvents(Game &game) override;

    void Update(Game& game, float time) override;

    void Draw(Game &game) override;

    void Init(Game& game) override;

private:
	Level _level;
};

