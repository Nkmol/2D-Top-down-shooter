//
// Created by Mevlüt Özdemir on 29-11-17.
//

#include "Shotgun.h"

Shotgun::Shotgun(int _damage, float fireRate) : Weapon(_damage, "Saiga-12", 5, fireRate, "shotgun") {
	type = "shotgun";
}
