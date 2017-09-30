//
// Created by Ahmad Rahimi on 9/25/17.
//

#include <SDL.h>
#include "assetsmanager.h"
#include <SDL_image.h>
#include <iostream>

AssetsManager* AssetsManager::assetsManager;

AssetsManager::AssetsManager() {

}
AssetsManager::~AssetsManager(){

}
SDL_Surface* AssetsManager::LoadImage(const std::string &filePath) {
    if (this->sprites.count(filePath) == 0) {
        this->sprites[filePath] = IMG_Load(filePath.c_str());
    }
    return this->sprites[filePath];
}

AssetsManager* AssetsManager::GetManager() {
    if (!assetsManager){
        assetsManager = new AssetsManager;
    }
    return assetsManager;
}