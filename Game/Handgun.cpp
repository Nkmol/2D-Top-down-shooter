//
// Created by Mevlüt Özdemir on 29-11-17.
//

#include "Handgun.h"

Handgun::Handgun(int _damage, float fireRate) : Weapon(_damage, "Glock", 10, fireRate, "pistol") {
	type = "handgun";
}
