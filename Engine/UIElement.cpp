#include "UIElement.h"

UIElement::UIElement(Point position, float lifetime) : _coordinates(position), _lifetime(lifetime)
{

}

void UIElement::Update(float time)
{
	if (_lifetime > 0)
		_livingtime += time;
}

void UIElement::Center()
{
	// Seems that X is already centred?
	const auto diff = config::WINDOW_CENTER - Point(0, _texture.width / 2.0);
	_rect = { int(diff.x), int(diff.y), _texture.width, _texture.height };
}