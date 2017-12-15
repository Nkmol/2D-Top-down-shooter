//
// Created by Mevlüt Özdemir on 14-12-17.
//

#ifndef SHOOTER_EXPLOSIONFACTORY_H
#define SHOOTER_EXPLOSIONFACTORY_H


#include "Explosion.h"

class ExplosionFactory {

private:
    std::map<string, Explosion> explosions;

    static ExplosionFactory *sInstance;

    ExplosionFactory();

public:
    static ExplosionFactory& Instance();

    ExplosionFactory(ExplosionFactory const &) = delete;

    void operator=(ExplosionFactory const &) = delete;

    Explosion GetExplosion(string name, Point point);

    Explosion GetRandomExplosion(Point point);
};


#endif //SHOOTER_EXPLOSIONFACTORY_H
