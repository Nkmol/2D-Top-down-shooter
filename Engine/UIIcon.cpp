#include "UIIcon.h"

UIIcon::UIIcon(const std::string token, const Point& position) : UIIcon(token, position, 100, 0)
{

}

UIIcon::UIIcon(const std::string token, const Point& position, int opacity, float lifetime)
	: UIElement(position, lifetime), _token(token), _opacity(opacity)
{
	LoadTexture();
}

void UIIcon::Draw()
{
	RenderManager::Instance().DrawTexture(_texture.GetPointer(), nullptr, &_rect, _angle);
}

void UIIcon::SetOpacity(int value)
{
	_opacity = value;
	SDL_SetTextureAlphaMod(_texture.GetPointer(), value);
}

void UIIcon::LoadTexture()
{
	_texture = Texture(AssetManager::Instance().LoadSurface(_token));
	SDL_SetTextureAlphaMod(_texture.GetPointer(), _opacity);
	_rect = { int(_coordinates.x), int(_coordinates.y), _texture.width, _texture.height };
}