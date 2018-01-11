//
// Created by Ahmad Rahimi on 12/20/17.
//

#ifndef SHOOTER_DROPABLEFACTORY_H
#define SHOOTER_DROPABLEFACTORY_H

#include "DropableObject.h"

class DropableFactory {
private:
    static DropableFactory *sInstance;
    std::vector<DropableObject> dropables;
public:
    int dropChance = 1;
    static DropableFactory& Instance();
    DropableFactory();
    DropableObject getDropable(int i);
};


#endif //SHOOTER_DROPABLEFACTORY_H
