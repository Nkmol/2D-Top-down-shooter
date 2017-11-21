#include "MapManager.h"

using namespace std;

MapManager& MapManager::Instance()
{
	static MapManager sInstance;

	return sInstance;
}

MapManager::MapManager()
{
	mapTexture = nullptr;
}

void MapManager::Init(const string input)
{
	tmx.load(input.c_str());
	string tileset = "content/map/" + tmx.tilesetList.at(0).source;
	tsx.load(tileset.c_str());

	SDL_Surface* spritesheet = AssetManager::getInstance().loadSurface(tsx.tileset.image.source.c_str());
	if (!spritesheet)
		cout << SDL_GetError() << endl;
	mapTexture = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), spritesheet);
	SDL_FreeSurface(spritesheet);
	GetTilesMap();
	GetTileLayers();
}

void MapManager::Render()
{
	const int tileWidth = tmx.mapInfo.tileWidth;
	const int tileHeight = tmx.mapInfo.tileHeight;
	const int width = tmx.mapInfo.width;
	const int height = tmx.mapInfo.height;
	
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.w = tileWidth;
	srcRect.h = tileHeight;
	destRect.w = tileWidth;
	destRect.h = tileHeight;

	
	int counter = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			destRect.y = i*tileWidth;
			destRect.x = j*tileHeight;
			
			if (atoi(tileLayers.at(0).at(counter).c_str()) != 0) {
				RenderManager::Instance().BlitSurface(mapTexture, &tilesMap.at(atoi(tileLayers.at(0).at(counter).c_str())), &destRect);
			}

			if (atoi(tileLayers.at(1).at(counter).c_str()) != 0) {
				collidables.push_back({ destRect.x, destRect.y, tileWidth, tileHeight });
				RenderManager::Instance().BlitSurface(mapTexture, &tilesMap.at(atoi(tileLayers.at(1).at(counter).c_str())), &destRect);
			}
			counter++;
		}
	}
}

void MapManager::RenderTilesText()
{
	for (std::map<std::string, TMX::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); ++it) {
		std::cout << std::endl;
		std::cout << "Tile Layer Name: " << it->first << std::endl;
		std::cout << "Tile Layer Visibility: " << tmx.tileLayer[it->first].visible << std::endl;
		std::cout << "Tile Layer Opacity: " << tmx.tileLayer[it->first].opacity << std::endl;
		std::cout << "Tile Layer Properties:" << std::endl;
		if (tmx.tileLayer[it->first].property.size() != 0) {
			for (std::map<std::string, std::string>::iterator it2 = tmx.tileLayer[it->first].property.begin(); it2 != tmx.tileLayer[it->first].property.end(); ++it2) {
				std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
			}
		}
		std::cout << "Tile Layer Data Encoding: " << tmx.tileLayer[it->first].data.encoding << std::endl;
		if (tmx.tileLayer[it->first].data.compression != "none") {
			std::cout << "Tile Layer Data Compression: " << tmx.tileLayer[it->first].data.compression << std::endl;
		}
		std::cout << "Tile Layer Data Contents: " << tmx.tileLayer[it->first].data.contents << std::endl;
	}
}

template<typename Out>
void MapManager::Split(const std::string &s, char delim, Out result)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, ','))
	{
		int startPos = item.find("\r\n");
		if (startPos >= 0)
			item.erase(startPos, 2);
		*(result++) = item;
	}
}

void MapManager::GetTilesMap()
{
	const int columns = tsx.tileset.columns;
	const int tileWidth = tsx.tileset.tileWidth;
	const int tileHeight = tsx.tileset.tileHeight;
	
	int counter = 1;

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			SDL_Rect rect;
			rect.h = tileHeight;
			rect.w = tileWidth;
			rect.x = j * tileWidth;
			rect.y = i * tileHeight;
			tilesMap.emplace(counter, rect);
			counter++;
			if (counter == tsx.tileset.tilecount)
				break;
		}
	}
}

void MapManager::GetTileLayers()
{
	for (std::map<std::string, TMX::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); ++it) {
		string content = tmx.tileLayer[it->first].data.contents;

		vector<string> tiles;
		string next;

		Split(content, ',', std::back_inserter(tiles));

		tileLayers.push_back(tiles);
	}
}
