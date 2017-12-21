#include <utility>

#include "UIText.h"
#include "../Game/Config.h"


UIText::UIText(const std::string& text, const unsigned fontSize) : UIText(text, fontSize, { 0, 0 }, { 0, 0, 0, 1 })
{
}

UIText::UIText(const std::string& text, const unsigned fontSize, const Point& position) : UIText(text, fontSize, position, {0, 0, 0, 1})
{
}

UIText::UIText(std::string  text, const unsigned fontSize, const Point& position, const RGBA& colour) : GameObject(position, config::width + 100, config::width + 100), _colour(colour), _text(std::move(text)) {
	auto font = AssetManager::Instance().LoadFont("OpenSans-Regular", fontSize);

	_surface = unique_ptr<SDL_Surface, CustomDeleter>(TTF_RenderText_Blended(font.get(), _text.c_str(), _colour));
	_rect = { int(_coordinates.x), int(_coordinates.y), _surface->w, _surface->h };
}

void UIText::Draw()
{
	if (!_surface.get()) return;

	RenderManager::Instance().DrawTexture(*_surface, nullptr, _rect, angle);
}

void UIText::Center()
{
	// Seems that X is already centred?
	const auto diff = RenderManager::WINDOW_CENTER - Point(0, _surface->w / 2.0);
	_rect = {int(diff.x), int(diff.y), _surface->w, _surface->h};
}

UIText::~UIText() = default;
