//
// Created by Ahmad Rahimi on 11/9/17.
//


#include "moveableobject.h"

MoveableObject::MoveableObject() {}

MoveableObject::MoveableObject(const std::string &filePath, float posX, float posY, int partnumber) : _x(posX), _y(posY), _partnumber(partnumber) {
    this->_sprite = SDL_CreateTextureFromSurface(RenderManager::GetRenderManager()->GetRenderer(), RenderManager::GetRenderManager()->LoadImage(filePath));

    if (this->_sprite == NULL){
        printf(SDL_GetError());
    }
}

MoveableObject::~MoveableObject() {}

void MoveableObject::draw(float x, float y, double angle) {
//    try {
    int w, h;
    SDL_QueryTexture(this->_sprite, NULL, NULL, &w, &h);
    SDL_Rect destinationRectangle = {int(x), int(y), w, h};
    RenderManager::GetRenderManager()->BlitSurface(this->_sprite, NULL, &destinationRectangle, angle);
//    }catch (int e){
//        std::cout << "An exception occurred. Exception Nr. " << e << '\n';
//    }
}

void MoveableObject::update() {

}
