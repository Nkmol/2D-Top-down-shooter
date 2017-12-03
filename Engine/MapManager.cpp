#include "MapManager.h"

using namespace std;

MapManager& MapManager::Instance()
{
	static MapManager sInstance;

	return sInstance;
}

const std::vector<GameObject>* MapManager::getCollidables() const
{
	return &collidables;
}

MapManager::MapManager()
{
	mapTexture = nullptr;
}

void MapManager::Init(const string input)
{
	tmx.load(input.c_str());
	string tileset = "../content/map/" + tmx.tilesetList.at(0).source;
	tsx.load(tileset.c_str());

	SDL_Surface* spritesheet = AssetManager::Instance().loadSurface(tsx.tileset.image.source.c_str());
	if (!spritesheet)
		cout << SDL_GetError() << endl;
	
	GetTilesMap();
	GetTileLayers();
	const int tileWidth = tmx.mapInfo.tileWidth;
	const int tileHeight = tmx.mapInfo.tileHeight;
	const int width = tmx.mapInfo.width;
	const int height = tmx.mapInfo.height;

	SDL_Rect destRect;
	destRect.w = tileWidth;
	destRect.h = tileHeight;

	Uint32 rmask, gmask, bmask, amask;
	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
    #endif

	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, width*tileWidth, height*tileHeight, 32,
													rmask, gmask, bmask, amask);
	std::cout << SDL_GetError() << endl;
	int counter = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			destRect.y = i*tileWidth;
			destRect.x = j*tileHeight;

			if (tileLayers.at(0).at(counter) != 0) {
				if (SDL_BlitSurface(spritesheet, &tilesMap.at(tileLayers.at(0).at(counter)), tempSurface, &destRect) != 0)
					std::cout << SDL_GetError() << endl;
			}

			if (tileLayers.at(1).at(counter) != 0) {
				collidables.push_back({ Point((float)tileWidth*j, (float)tileHeight*i), tileWidth, tileHeight });
				if (SDL_BlitSurface(spritesheet, &tilesMap.at(tileLayers.at(1).at(counter)), tempSurface, &destRect) != 0)
					std::cout << SDL_GetError() << endl;
			}
			counter++;
		}
	}

	mapTexture = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), tempSurface);
	SDL_FreeSurface(spritesheet);
	SDL_FreeSurface(tempSurface);
}

void MapManager::Render()
{
	mapRect.x = mapRect.y = 0;
	mapRect.w = tmx.mapInfo.width * tmx.mapInfo.tileWidth;
	mapRect.h = tmx.mapInfo.height * tmx.mapInfo.tileHeight;

	RenderManager::Instance().DrawTexture(mapTexture, &mapRect, NULL);
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

	for (int i = 0; i < tsx.tileset.tilecount / columns; i++)
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
	vector<vector<string>> tempLayers;
	for (std::map<std::string, TMX::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); ++it) {
		string content = tmx.tileLayer[it->first].data.contents;

		vector<string> tiles;
		string next;

		Split(content, ',', std::back_inserter(tiles));

		tempLayers.push_back(tiles);
	}
	int counter = 0;
	for (auto layer : tempLayers) {
		vector<int> intlayer;
		for (string tile : tempLayers.at(counter)) {
			intlayer.push_back(atoi(tile.c_str()));
		}
		tileLayers.push_back(intlayer);
		counter++;
	}
}

const SDL_Rect &MapManager::GetMapRect() const {
	return mapRect;
}