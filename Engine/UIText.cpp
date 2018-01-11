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
	_texture = Texture(TTF_RenderText_Blended(_font.get(), _text.c_str(), _colour));
	_rect = { int(_coordinates.x), int(_coordinates.y), _texture.width, _texture.height };
}

void UIText::Draw()
{
	if (!_texture.GetTexture()) return;

	RenderManager::Instance().DrawTexture(_texture.GetTexture(), nullptr, &_rect, _angle);
}

void UIText::Center()
{
	// Seems that X is already centred?
	const auto diff = config::WINDOW_CENTER - Point(0, _texture.width / 2.0);
	_rect = {int(diff.x), int(diff.y), _texture.width, _texture.height };
}

void UIText::ChangeText(const std::string& text)
{
	if (text == _text) return;

	_text = text;

	LoadSurface();
}
