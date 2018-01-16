//
// Created by Mevlüt Özdemir on 29-11-17.
//

#include "Shotgun.h"
#include "Bullet.h"
#include "Point.h"

Shotgun::Shotgun(int _damage, float fireRate) : Weapon(_damage, "Saiga-12", 5, fireRate, "shotgun") {
	type = "shotgun";
}

std::vector<Bullet> Shotgun::GetBullet(int angle, Point coordinates, bool &isCheatActive) {
	std::vector<Bullet> bullets;
	if (!HasBullets()) return bullets;

	for (int i = -1; i < 2; i++)
	{
		Bullet bullet("bullet", coordinates, _damage);
		if (fireRate != standardFireRate) {
			float s1 = (standardFireRate / fireRate)*bullet.GetSpeed();
			bullet.SetSpeed(s1);
		}
		bullet.SetAngle(angle + (i * 3));

		if (isCheatActive) bullet.SetDamage(10000000);

		bullets.emplace_back(bullet);
	}	
	if (!isCheatActive)
		shooted++;
		
	PlaySound(_soundName);
	
	_triggerDown = true;

	return bullets;
}
