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
		swap(first._visible, second._visible);
		swap(first._spriteToken, second._spriteToken);
		swap(first._sprite, second._sprite);
		//first._sprite = unique_ptr<SDL_Texture, CustomDeleter>(move(second._sprite.get()), move(second._sprite.get_deleter()));
	}
public:
	GameObject(Point coordinates, int width, int height);
	GameObject(const std::string & _spriteToken, const Point coordinates);
	GameObject(const GameObject& other);
	GameObject& operator=(GameObject that);

	
	void SetIsCollidable(bool isCollidable);

	const int GetMidX() const;
	const int GetMidY() const;
	int GetWidth() const;
	int GetHeight() const;
	void SetCoordinates(const Point & value);
	const Point &GetCoordinates() const;
	const SDL_Rect GetRect() const;
	void Draw();
	int GetAngle() const;
	void SetAngle(const int angle);
	void Hide();
	bool IsVisible() const;
	const int GetRadius() const ;
	string GetSpriteToken() const;
	bool GetIsCollidable() { return _isCollidable; }

protected:
	GameObject();
	int width, height, angle;
	float radius, midX, midY;
	Point _coordinates;
	bool _visible;
	bool _isCollidable = false;
	unique_ptr<Texture> _sprite;
    std::string _spriteToken;
};

