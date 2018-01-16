#pragma once

#include <climits>
#include "Texture.h"
#include "Point.h"

class UIElement
{
public:
	struct RGBA
	{
		Uint8 R, G, B, A;

		// Implicit from struct to SDL_Color
		operator SDL_Color() const {
			// Use Implicit constructor of SDL_Color
			return { R, G, B, A };
		}
	};
protected:
	Texture _texture{};
	Point _coordinates;
	int _angle{};
	SDL_Rect _rect{};

	float _lifetime = 0;
	float _livingtime = 0;
public:
	UIElement(Point position, float lifetime);

	virtual void Draw() = 0;
	void Center();

	void Update(float time);
	const bool Destroyable() const { return _livingtime > _lifetime; }
	void Destroy() { _livingtime = INT_MAX; }
};