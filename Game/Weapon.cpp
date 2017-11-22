//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include <iostream>
#include <Weapon.h>

void Weapon::addBullets(Bullet &bullet, int amount) {
    for (int i = 0; i < amount; ++i) {
        bullets.push_back(bullet);
    }
}


void Weapon::shoot(int angle, float xPos, float yPos) {
    for (auto &bullet : bullets) {
        if (!bullet.isVisible()) {
            bullet.makeVisible();
            bullet.setXPos(xPos);
            bullet.setYPos(yPos);

            bullet.setAngle(angle);
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


