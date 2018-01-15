//
// Created by Mevlüt Özdemir on 14-12-17.
//

#include <InputManager.h>
#include "ExplosionFactory.h"

ExplosionFactory *ExplosionFactory::_instance = nullptr;

ExplosionFactory &ExplosionFactory::Instance() {
    static ExplosionFactory _instance;

    return _instance;
}

ExplosionFactory::ExplosionFactory() {
    explosions = {
            {"short",   Explosion("short", 4, 0.1)},
            {"shield",  Explosion("shield", 4, 0.1)},
            {"default", Explosion("default", 25, 0.1)},
            {"long",    Explosion("long", 20, 0.01)},
            {"middle",  Explosion("middle", 28, 0.1)},
            {"blood-1", Explosion("blood-1", 16, 0.1)},
            {"blood-2", Explosion("blood-2", 14, 0.1)},
            {"blood-3", Explosion("blood-3", 9, 0.1)}

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


