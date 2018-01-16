//
// Created by Ahmad Rahimi on 12/20/17.
//

#include "DropableFactory.h"
#include "PowerupHP.h"
#include "PowerupFastShot.h"

DropableFactory::DropableFactory() {
    const Point p = {0,0};
    _dropables.emplace_back(PowerupHP(p));
    _dropables.emplace_back(PowerupFastShot(p));
}

DropableObject DropableFactory::GetDropable(int i) {
    DropableObject dropableObject = _dropables.at(i);
    return dropableObject;
}

DropableFactory &DropableFactory::Instance() {
    static DropableFactory _instance;
    return _instance;
}
