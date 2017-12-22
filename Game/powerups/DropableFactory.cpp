//
// Created by Ahmad Rahimi on 12/20/17.
//

#include "DropableFactory.h"
#include "PowerupHP.h"
#include "PowerupFastShot.h"

DropableFactory::DropableFactory() {
    const Point p = {0,0};
    dropables.emplace_back(PowerupHP(p));
    dropables.emplace_back(PowerupFastShot(p));
}

DropableObject DropableFactory::getDropable(int i) {
    DropableObject dropableObject = dropables.at(i);
    return dropableObject;
}

DropableFactory &DropableFactory::Instance() {
    static DropableFactory sInstance;
    return sInstance;
}
