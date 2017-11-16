#include <iostream>
#include "../tmx/include/TMXParser.h"
#include "../tmx/include/TSXParser.h"
#include "AssetManager.h"
#include "RenderManager.h"
#include "CollidableObject.h"
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <SDL.h>

class TMXManager {
public:
	TMXManager(TMXManager const&) = delete;
	void operator=(TMXManager const&) = delete;
	static TMXManager& Instance();
	std::vector<CollidableObject> collidables;

	void Init(const std::string input);
	void Render();
	void RenderTilesText();
private:
	TMX::Parser tmx;
	TSX::Parser tsx;
	static TMXManager sInstance;
	SDL_Texture* mapTexture;
	TMXManager();

	template<typename Out>
	void Split(const std::string &s, char delim, Out result);
	std::map<int, SDL_Rect> GetTilesMap();
	
};