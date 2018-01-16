//
// Created by Ahmad Rahimi on 12/20/17.
//

#ifndef SHOOTER_DROPABLEFACTORY_H
#define SHOOTER_DROPABLEFACTORY_H

#include "DropableObject.h"

class DropableFactory {
private:
    static DropableFactory *_instance;
    std::vector<DropableObject> _dropables;
public:
    int _dropChance = 1;
    static DropableFactory& Instance();
    DropableFactory();
    DropableObject GetDropable(int i);
};


#endif //SHOOTER_DROPABLEFACTORY_H
