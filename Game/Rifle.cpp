//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Rifle.h"

Rifle::Rifle(int _damage, float fireRate) : Weapon(_damage, "AR-15", 100, fireRate,"assaultrifle") {
	type = "rifle";
	_automatic = true;
}
