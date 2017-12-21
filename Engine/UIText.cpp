#include <utility>

#include "UIText.h"
#include "../Game/Config.h"

UIText::UIText() : UIText("", 14)
{
}

UIText::UIText(const std::string& text, const unsigned fontSize) : UIText(text, fontSize, { 0, 0 })
{
}

UIText::UIText(const std::string& text, const unsigned fontSize, const Point& position) : UIText(text, fontSize, position, { 255, 255, 255, 1 })
{
}

UIText::UIText(const std::string& text, const unsigned fontSize, const Point& position, const RGBA& colour) : GameObject(position, 0, 0), _colour(colour), _text(text) 
{
	_font = AssetManager::Instance().LoadFont("OpenSans-Regular", fontSize);

	if (text.empty()) return;

	LoadSurface();
}

void UIText::LoadSurface()
{
	_surface = TTF_RenderText_Blended(_font, _text.c_str(), _colour);
	_rect = { int(_coordinates.x), int(_coordinates.y), _surface->w, _surface->h };
}

void UIText::Draw()
{
	if (!_surface) return;

	RenderManager::Instance().DrawTexture(*_surface, nullptr, _rect, angle);
}

void UIText::Center()
{
	// Seems that X is already centred?
	const auto diff = RenderManager::WINDOW_CENTER - Point(0, _surface->w / 2.0);
	_rect = {int(diff.x), int(diff.y), _surface->w, _surface->h};
}

void UIText::ChangeText(const std::string& text)
{
	if (text == _text) return;

	_text = text;

	LoadSurface();
}

UIText::~UIText() = default;
