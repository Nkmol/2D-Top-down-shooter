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

class MapManager {
public:
	MapManager(MapManager const&) = delete;
	void operator=(MapManager const&) = delete;
	static MapManager& Instance();
	const std::vector<GameObject>* GetCollidables() const;

	void Init(const std::string input);
	void Render();
	void RenderTilesText();
	const SDL_Rect &GetMapRect() const;

private:
	SDL_Rect _mapRect = SDL_Rect();
	std::vector<GameObject> _collidables;
	TMX::Parser _tmx;
	TSX::Parser _tsx;
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