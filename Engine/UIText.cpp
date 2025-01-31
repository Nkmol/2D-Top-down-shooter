#include "UIText.h"

UIText::UIText() : UIText("", 14)
{
}

UIText::UIText(const std::string& text, const unsigned fontSize, float lifetime) : UIText(text, fontSize, { 0, 0 }, lifetime)
{
}

UIText::UIText(const std::string& text, const unsigned fontSize, const Point& position, float lifetime) : UIText(text, fontSize, position, { 255, 255, 255, 1 }, lifetime)
{
}

UIText::UIText(const std::string& text, const unsigned fontSize, const Point& position, const RGBA& colour, float lifetime) : UIElement(position, lifetime), _colour(colour), _text(text)
{
	_font = AssetManager::Instance().LoadFont("OpenSans-Regular", fontSize);

	if (text.empty()) return;

	LoadSurface();
}

void UIText::LoadSurface()
{
	_texture = Texture(TTF_RenderText_Blended(_font.GetPointer(), _text.c_str(), _colour));
	_rect = { int(_coordinates.x), int(_coordinates.y), _texture.width, _texture.height };
}

void UIText::Draw()
{
	if (!_texture.GetPointer()) return;

	RenderManager::Instance().DrawTexture(_texture.GetPointer(), nullptr, &_rect, _angle);
}

void UIText::ChangeText(const std::string& text)
{
	if (text == _text) return;

	_text = text;

	LoadSurface();
}
