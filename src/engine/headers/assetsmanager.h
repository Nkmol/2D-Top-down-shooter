//
// Created by Ahmad Rahimi on 9/25/17.
//

#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <map>
#include <string>
#include <SDL.h>

using namespace std;

class AssetsManager {
public:
    AssetsManager();
    ~AssetsManager();

    SDL_Surface* LoadImage(const std::string &filePath);
    static AssetsManager* GetManager();


private:
    map<std::string, SDL_Surface*> sprites;
    static AssetsManager *assetsManager;

};
#endif //ASSETSMANAGER_H
