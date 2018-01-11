#include "MapManager.h"

using namespace std;

MapManager& MapManager::Instance()
{
	static MapManager _instance;

	return _instance;
}

MapManager::MapManager()
{
	_mapTexture = nullptr;
}

void MapManager::Init(const string input)
{
	std::string filepath = "../content/map/" + input;
	_tmx.load(filepath.c_str());
	string tileset = "../content/map/" + _tmx.tilesetList.at(0).source;
	_tsx.load(tileset.c_str());

	SDL_Surface* spritesheet = AssetManager::Instance().LoadSurface(_tsx.tileset.image.source.c_str());
	if (!spritesheet)
		cout << SDL_GetError() << endl;
	
	GetTilesMap();
	GetTileLayers();
	const int tileWidth = _tmx.mapInfo.tileWidth;
	const int tileHeight = _tmx.mapInfo.tileHeight;
	const int width = _tmx.mapInfo.width;
	const int height = _tmx.mapInfo.height;

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
		_newCollidables.emplace_back();
		for (int j = 0; j < width; j++)
		{
			destRect.y = i*tileWidth;
			destRect.x = j*tileHeight;

			if (_tileLayers.at(0).at(counter) != 0) {
				if (SDL_BlitSurface(spritesheet, &_tilesMap.at(_tileLayers.at(0).at(counter)), tempSurface, &destRect) != 0)
					std::cout << SDL_GetError() << endl;
			}

			GameObject gameObject{ Point((float)tileWidth*j, (float)tileHeight*i), tileWidth, tileHeight };
			_newCollidables.at(i).push_back(make_unique<GameObject>(gameObject));
			if (_tileLayers.at(1).at(counter) != 0) {				
				//collidables.push_back(gameObject);
				_newCollidables.at(i).at(j).get()->SetIsCollidable(true);
				if (SDL_BlitSurface(spritesheet, &_tilesMap.at(_tileLayers.at(1).at(counter)), tempSurface, &destRect) != 0)

					std::cout << SDL_GetError() << endl;
			}
			
			
			counter++;
		}
	}

	_mapTexture = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), tempSurface);
	SDL_FreeSurface(spritesheet);
	SDL_FreeSurface(tempSurface);
}

void MapManager::Render()
{
	_mapRect.x = _mapRect.y = 0;
	_mapRect.w = _tmx.mapInfo.width * _tmx.mapInfo.tileWidth;
	_mapRect.h = _tmx.mapInfo.height * _tmx.mapInfo.tileHeight;

	RenderManager::Instance().DrawTexture(_mapTexture, &_mapRect, NULL);
}

void MapManager::RenderTilesText()
{
	for (std::map<std::string, TMX::TileLayer>::iterator it = _tmx.tileLayer.begin(); it != _tmx.tileLayer.end(); ++it) {
		std::cout << std::endl;
		std::cout << "Tile Layer Name: " << it->first << std::endl;
		std::cout << "Tile Layer Visibility: " << _tmx.tileLayer[it->first]._visible << std::endl;
		std::cout << "Tile Layer Opacity: " << _tmx.tileLayer[it->first].opacity << std::endl;
		std::cout << "Tile Layer Properties:" << std::endl;
		if (_tmx.tileLayer[it->first].property.size() != 0) {
			for (std::map<std::string, std::string>::iterator it2 = _tmx.tileLayer[it->first].property.begin(); it2 != _tmx.tileLayer[it->first].property.end(); ++it2) {
				std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
			}
		}
		std::cout << "Tile Layer Data Encoding: " << _tmx.tileLayer[it->first].data.encoding << std::endl;
		if (_tmx.tileLayer[it->first].data.compression != "none") {
			std::cout << "Tile Layer Data Compression: " << _tmx.tileLayer[it->first].data.compression << std::endl;
		}
		std::cout << "Tile Layer Data Contents: " << _tmx.tileLayer[it->first].data.contents << std::endl;
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
	const int columns = _tsx.tileset.columns;
	const int tileWidth = _tsx.tileset.tileWidth;
	const int tileHeight = _tsx.tileset.tileHeight;
	
	int counter = 1;

	for (int i = 0; i < _tsx.tileset.tilecount / columns; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			SDL_Rect rect;
			rect.h = tileHeight;
			rect.w = tileWidth;
			rect.x = j * tileWidth;
			rect.y = i * tileHeight;
			_tilesMap.emplace(counter, rect);
			counter++;
			if (counter == _tsx.tileset.tilecount)
				break;
		}
	}
}

void MapManager::GetTileLayers()
{
	vector<vector<string>> tempLayers;
	for (std::map<std::string, TMX::TileLayer>::iterator it = _tmx.tileLayer.begin(); it != _tmx.tileLayer.end(); ++it) {
		string content = _tmx.tileLayer[it->first].data.contents;

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
		_tileLayers.push_back(intlayer);
		counter++;
	}
}

const SDL_Rect &MapManager::GetMapRect() const {
	return _mapRect;
}

void MapManager::getNearbyCollidables(Point position, std::vector<GameObject*>* nearby)
{
	const int tileWidth = _tsx.tileset.tileWidth;
	const int tileHeight = _tsx.tileset.tileHeight;
	int radius = 2;
	int x = ((position.x) / tileWidth) < 0 ? 0 : ((position.x ) / tileWidth);
	int y = ((position.y ) / tileHeight) < 0 ? 0 : ((position.y) / tileHeight);

	for (int j = y - radius; j <= radius + y; j++)
	{
		if (j < 0 || j >= _newCollidables.size())
		{
		}
		else {
			for (int i = x - radius; i <= radius + x; i++)
			{
				if (i < 0 || i >= _newCollidables.at(j).size())
				{
				}
				else
					if(_newCollidables.at(j).at(i).get()->GetIsCollidable())
						nearby->push_back(_newCollidables.at(j).at(i).get());
			}
		}
	}
}