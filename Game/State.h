#pragma once

class Game;
class Event;

class State
{
public:
	virtual ~State() = default;

	virtual void Init(Game& game) = 0;

	virtual void HandleEvents(Game& game, Event& event) = 0;
	virtual void Update(Game& game, float time) = 0;
	virtual void Draw(Game& game) = 0;

	/*void ChangeState(Game& game, State* state) {
		game.ChangeState(state);
	}*/
	void SetHighestLevel(const int i) { _highestLevel = i; }

protected:
	State() { }
	int  _highestLevel = 1;
};
