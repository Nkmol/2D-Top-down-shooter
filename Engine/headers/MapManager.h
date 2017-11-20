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

class MapManager {
public:
	MapManager(MapManager const&) = delete;
	void operator=(MapManager const&) = delete;
	static MapManager& Instance();
	std::vector<CollidableObject> collidables;

	void Init(const std::string input);
	void Render();
	void RenderTilesText();
private:
	TMX::Parser tmx;
	TSX::Parser tsx;
	static MapManager sInstance;
	SDL_Texture* mapTexture;
	MapManager();
	std::map<int, SDL_Rect> tilesMap;
	vector<vector<string>> tileLayers;

	template<typename Out>
	void Split(const std::string &s, char delim, Out result);
	void GetTilesMap();
	void GetTileLayers();
	
};