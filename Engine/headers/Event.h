#pragma once
#include <SDL_events.h>

class Event
{
	SDL_Event _event;

public:
	SDL_Event* GetEvent() { return &_event; }
	const SDL_Event GetEventValue() const { return _event; }
};