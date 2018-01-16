#pragma once
#include <iostream>
#include "../tmx/include/TMXParser.h"
#include "../tmx/include/TSXParser.h"
#include "AssetManager.h"
#include "RenderManager.h"
#include "GameObject.h"
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <SDL.h>
#include "Point.h"
#include <memory>

class MapManager {
public:
	MapManager(MapManager const&) = delete;
	void operator=(MapManager const&) = delete;
	static MapManager& Instance();

	void Init(const std::string input);
	void Render();
	void RenderTilesText();
	const SDL_Rect &GetMapRect() const;

	void GetNearbyCollidables(Point position, std::vector<GameObject*>* nearby);

private:
	std::vector<std::vector<std::unique_ptr<GameObject>>> _newCollidables;

	SDL_Rect _mapRect = SDL_Rect();
	std::unique_ptr<TMX::Parser> _tmx;
	std::unique_ptr<TSX::Parser> _tsx;
	static MapManager _instance;
	SDL_Texture* _mapTexture;

	MapManager();
	std::map<int, SDL_Rect> _tilesMap;
	vector<vector<int>> _tileLayers;

	template<typename Out>
	void Split(const std::string &s, char delim, Out result);
	void GetTilesMap();
	void GetTileLayers();
	
};