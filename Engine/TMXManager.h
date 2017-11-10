#include <iostream>
#include "tmx/include/TMXParser.h"
#include "tmx/include/TSXParser.h"
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <SDL.h>
#include <SDL_image.h>

class TMXManager {
public:
	TMXManager(TMXManager const&) = delete;
	void operator=(TMXManager const&) = delete;
	static TMXManager* Instance();

	void Init(std::string input);
	void Render();
	void RenderTilesText();
private:
	TMX::Parser tmx;
	TSX::Parser tsx;
	static TMXManager* sInstance;
	SDL_Texture* mapTexture;
	SDL_Renderer* renderer;
	TMXManager();

	template<typename Out>
	void Split(const std::string &s, char delim, Out result);
	std::map<int, SDL_Rect> GetTilesMap();
	
};