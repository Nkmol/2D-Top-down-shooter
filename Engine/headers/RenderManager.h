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
#include "AssetManager.h"
using namespace std;

class RenderManager {
public:
	RenderManager(RenderManager const&) = delete;
	void operator=(RenderManager const&) = delete;

	RenderManager();
	~RenderManager();
	void CreateWindow(const std::string& title, bool fullscreen, const int width, const int height);

	SDL_Surface* LoadImage(const std::string &filePath);
	/* void BlitSurface
	* Drawing images on a screen
	*/
	void BlitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle, double angle = 0) const;

	/* void flip
	* Render everything on screen
	*/
	void Flip() const;

	/* void clear
	* Clear the screen
	*/
	void Clear() const;

	/* SDL_Renderer* getRenderer
	* Returns the renderer
	*/
	SDL_Renderer* GetRenderer() const;

	/* void DrawText
	* Draw Text on screen
	*/
	void DrawText(const std::string text, const int x, const int y, const int width, const int height, const double angle = 0) const;
	void DrawButton(int screen_width, int screen_height, int x, int y, std::string mediatoken);
	static RenderManager& Instance();


private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* newgameTexture;
	SDL_Texture* loadgameTexture;
	SDL_Texture* creditsTexture;
	map<std::string, SDL_Surface*> sprites;

	static RenderManager* sInstance;
};
#endif //RENDERMANAGER_H