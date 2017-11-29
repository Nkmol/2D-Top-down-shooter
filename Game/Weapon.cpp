//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Weapon.h"

#include <utility>

Weapon::Weapon(int damage, std::string name) : name{std::move(name)}, damage{damage} {

}


void Weapon::addBullets(Bullet &bullet, int amount) {
    for (int i = 0; i < amount; ++i) {
        shared_ptr<Bullet> b{new Bullet(bullet)};
        bullets.push_back(*b);
    }
}


void Weapon::shoot(int angle, float xPos, float yPos) {
    for (auto &bullet : bullets) {
        if (!bullet.isVisible()) {
            bullet.makeVisible();
            bullet.SetCoordinates(Point{xPos, yPos});
            bullet.setAngle(angle);
            shooted++;
            break;
        }
    }

}

void Weapon::updateBullets(float time) {
    for (auto &bullet : bullets) {
        if (bullet.isVisible()) {
            bullet.update(time);
        }
    }
}


void Weapon::drawBullets() {
    for (auto &bullet : bullets) {
        if (bullet.isVisible()) {
            bullet.draw();
        }
    }
}

const vector<Bullet> &Weapon::getBullets() const {
    return bullets;
}

int Weapon::totalBullets() const {
    if (bullets.empty()) return 0;

    return bullets.size();
}

std::string Weapon::getName() const {
    return this->name;
}

int Weapon::getShooted() const {
    return this->shooted;
}


