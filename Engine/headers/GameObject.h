#pragma once
#include <string>
#include <SDL_rect.h>
#include "Point.h"
#include "../Texture.h"
#include <memory>

class GameObject 
{
	/// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
	/// https://stackoverflow.com/questions/5695548/public-friend-swap-member-function
	friend void Swap(GameObject& first, GameObject& second) noexcept
	{
		// enable ADL (not necessary in our case, but good practice)
		/// https://stackoverflow.com/questions/28130671/how-does-using-stdswap-enable-adl
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		swap(first.width, second.width);
		swap(first.height, second.height);
		swap(first.angle, second.angle);
		swap(first.radius, second.radius);
		swap(first.midX, second.midX);
		swap(first._coordinates, second._coordinates);
		swap(first.visible, second.visible);
		swap(first.spriteToken, second.spriteToken);
		swap(first._sprite, second._sprite);
		//first._sprite = unique_ptr<SDL_Texture, CustomDeleter>(move(second._sprite.get()), move(second._sprite.get_deleter()));
	}
public:
	GameObject(Point coordinates, int width, int height);
	GameObject(const std::string & spriteToken, const Point coordinates);
	GameObject(const GameObject& other);
	GameObject& operator=(GameObject that);

	bool _isCollidable = false;
	void SetIsCollidable(bool isCollidable);
	const int getMidX() const;
	const int getMidY() const;
	int getWidth() const;
	int getHeight() const;
	void SetCoordinates(const Point & value);
	const Point &GetCoordinates() const;
	const SDL_Rect GetRect() const;
	void draw();
	int getAngle() const;
	void SetAngle(const int angle);
	void hide();
	bool isVisible() const;
	const int getRadius() const ;
	string GetSpriteToken() const;

protected:
	GameObject();
	int width, height, angle;
	float radius, midX, midY;
	Point _coordinates;
	bool visible;
	unique_ptr<Texture> _sprite;
    std::string spriteToken;
};

