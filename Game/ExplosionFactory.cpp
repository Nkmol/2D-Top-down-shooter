//
// Created by Mevlüt Özdemir on 14-12-17.
//

#include <InputManager.h>
#include "ExplosionFactory.h"

ExplosionFactory *ExplosionFactory::sInstance = nullptr;

ExplosionFactory &ExplosionFactory::Instance() {
    static ExplosionFactory sInstance;

    return sInstance;
}

ExplosionFactory::ExplosionFactory() {
    explosions = {
            {"short",   Explosion("short", 4, 0.1)},
            {"shield",  Explosion("shield", 4, 0.1)},
            {"default", Explosion("default", 25, 0.1)},
            {"long",    Explosion("long", 216, 0.1)},
    };
}

Explosion ExplosionFactory::GetExplosion(string name, Point point) {
    auto it = explosions.find(name);

    if (it != explosions.end()) {
        Explosion &explosion = it->second;
        explosion.SetPoint(point);
        return explosion;
    }

    return GetRandomExplosion(point);
}

Explosion ExplosionFactory::GetRandomExplosion(Point point) {
    int random = rand() % explosions.size();
    int counter = 0;

    for (auto &element : explosions) {
        if (random == counter) {
            Explosion &explosion = element.second;
            explosion.SetPoint(point);
            return explosion;
        }
        counter++;
    }
}


