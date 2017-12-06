#pragma once

#include <memory>
#include "State.h"
#include "FlockController.h"

class Player;
class MoveableObject;

class PlayingState : public State {
public:
    PlayingState();

    ~PlayingState();

    void HandleEvents(Game &game) override;

    void Update(Game& game, float time) override;

    void Draw(Game &game) override;

    void Init() override;

private:
    // Todo might actually need to be GameObject
    // Use Pointer so Slicing will not occur

    std::vector<std::shared_ptr<MoveableObject>> _objs;
	std::shared_ptr<Player> _player;
    FlockController flockController;

};

