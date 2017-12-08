#pragma once

class Game;
class Event;
class MenuState;

class MenuSubState
{
public:
	virtual ~MenuSubState() = default;

	virtual void Init() = 0;

	virtual void HandleEvents(Game& game, MenuState& state, Event& ev) = 0;
	virtual void Update(Game& game, float time) = 0;
	virtual void Draw() = 0;

	/*void ChangeState(Game& game, State* state) {
	game.ChangeState(state);
	}*/

protected:
	MenuSubState() { }
};
