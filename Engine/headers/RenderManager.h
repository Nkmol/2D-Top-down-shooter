//
// Created by Ahmad Rahimi on 9/25/17.
//

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Point.h"
#include "../../Game/Config.h"

using namespace std;

class RenderManager {
public:
	inline static const Point WINDOW_CENTER = { config::height / 2, config::width / 2 };

	RenderManager(RenderManager const&) = delete;
	void operator=(RenderManager const&) = delete;

	RenderManager();
	~RenderManager();
	void CreateWindow(const std::string& title, bool fullscreen, const int width, const int height);

	SDL_Surface* LoadImage(const std::string &filePath);

	/* void DrawTexture
	* Drawing images on a screen
	*/
	void DrawTexture(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle, double angle = 0) const;
	
	/* void Render
	* Render everything on screen
	*/
	void Render() const;

	/* void clear
	* Clear the screen
	*/
	void Clear() const;

	/* SDL_Renderer* getRenderer
	* Returns the renderer
	*/
	SDL_Renderer* GetRenderer() const;

	static RenderManager& Instance();

	SDL_Window* GetWindow() const;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	map<std::string, SDL_Surface*> _sprites;
	TTF_Font* _font;
	int _fontHeight = 0;
	static RenderManager* _instance;
};
#endif //RENDERMANAGER_H