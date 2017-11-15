//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Bullet.h"

Bullet::Bullet(const string &filePath, float xPos, float yPos) : MoveableObject(filePath, xPos, yPos) {}

void Bullet::makeVisible(){
    this->visible = true;
}

void Bullet::makeInvisible(){
    this->visible = false;
}