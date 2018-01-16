#include "AssetManager.h"
#include "Button.h"
#include "Event.h"
#include "InputManager.h"

Button::Button(const std::string& mediatoken, const Point& startPosition, const Point& size) : GameObject(startPosition, size.x, size.y)
{
	GameObject::_sprite = AssetManager::Instance().LoadTexture(mediatoken).release();
	GameObject::_spriteToken = mediatoken;
}

Button::Button(const std::string& mediatoken, const Point& startPosition, const Point& size, const DelegateFunction&& delegate) : Button(mediatoken, startPosition, size)
{
	_clickFuncton = move(delegate);
}

Button::Button() {}

bool Button::IsClicked(Event ev) const
{
	if (!InputManager::Instance().IsMouseClicked(ev)) return false;

	auto& mouse = ev.GetEventValue().button;
	return mouse.x > _coordinates.x && mouse.x < _coordinates.x + width && mouse.y > _coordinates.y && mouse.y < _coordinates.y + height;
}

void Button::Click() const
{
	_clickFuncton();
}
