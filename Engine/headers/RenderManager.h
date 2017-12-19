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

using namespace std;

class RenderManager {
public:
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

	/* void DrawText
	* Draw Text on screen
	*/
	void DrawText(const std::string text, const int x, const int y, int width, int height, const double angle = 0, const int opacity = 0, const int r = 255, const int g = 255, const int b = 255);

	static RenderManager& Instance();

	SDL_Window* GetWindow() const;

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	map<std::string, SDL_Surface*> sprites;
	TTF_Font* font;
	int fontHeight = 0;
	static RenderManager* sInstance;
};
#endif //RENDERMANAGER_H