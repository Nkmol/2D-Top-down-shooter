#include "TextComponent.h"
#include "RenderManager.h"

TextComponent::TextComponent(std::string* text, Point pos, int w, int h, double angle)
	: IHudComponent(pos, w, h, angle), _text{ text }
{

}

void TextComponent::Update(float time)
{

}

void TextComponent::Draw()
{
	RenderManager::Instance().DrawText(*_text, _pos.x, _pos.y, _w, _h, _angle, 122);
}
