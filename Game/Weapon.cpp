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
            bullet.setDestinationXPos(20);
            bullet.setDestinationYPos(20);
            bullet.setAngle(angle);
            break;
        }
    }

}

void Weapon::update(float time) {
    for (auto &bullet : bullets) {
        if (bullet.isVisible()) {
            bullet.makeInvisible();
        }
    }
}


void Weapon::drawBullets() {
    int counter = 0;
    for (auto &bullet : bullets) {
        if (bullet.isVisible()) {
            bullet.draw();
            cout << counter << endl;
            cout << "X: " << bullet.getXPos() << endl;
            cout << "Y: " << bullet.getYPos() << endl << endl;
            counter++;
        }
    }
}


