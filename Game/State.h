#pragma once

class Game;

class State
{
public:
	virtual ~State() = default;

	virtual void Init() = 0;

	virtual void HandleEvents(Game& game) = 0;
	virtual void Update(Game& game, float time) = 0;
	virtual void Draw(Game& game) = 0;

	/*void ChangeState(Game& game, State* state) {
		game.ChangeState(state);
	}*/

protected:
	State() { }
};
