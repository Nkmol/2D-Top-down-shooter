#include "TextComponent.h"
#include "RenderManager.h"

TextComponent::TextComponent(std::string text, Point pos, int w, int h, float time, double angle)
	: IHudComponent(pos, w, h, time, angle), _text{ text }
{

}

void TextComponent::Update(float time)
{
	if (_lifetime > 0)
		_livingtime += time;
}

void TextComponent::Draw()
{
	//RenderManager::Instance().DrawText(_text, _pos.x, _pos.y, _w, _h, _angle);
}

