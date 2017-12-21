#include "UIText.h"
#include "../Game/Config.h"


UIText::UIText(const std::string& text, const unsigned fontSize) : UIText(text, fontSize, { 0, 0 }, { 0, 0, 0, 1 })
{
}

UIText::UIText(const std::string& text, const unsigned fontSize, const Point& position) : UIText(text, fontSize, position, {0, 0, 0, 1})
{
}

UIText::UIText(const std::string& text, const unsigned fontSize, const Point& position, const RGBA& colour) : GameObject(position, config::width + 100, config::width + 100), _colour(colour), _text(text) {
	_font = AssetManager::Instance().LoadFont("OpenSans-Regular", fontSize);
}

void UIText::Draw() const
{
	if (!_font.get()) return;

	auto* text = TTF_RenderText_Blended(_font.get(), _text.c_str(), _colour);
	SDL_Rect dst = { _coordinates.x, _coordinates.y, text->w, text->h };

	RenderManager::Instance().DrawTexture(*text, nullptr, dst, angle);
}

void UIText::Center()
{
	
}

UIText::~UIText() = default;
