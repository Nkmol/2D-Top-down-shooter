#include "PhysicsManager.h"


PhysicsManager::PhysicsManager()
{
	if(collidables == NULL)
		collidables = MapManager::Instance().getCollidables();
}

PhysicsManager::~PhysicsManager()
{
}

//how to call: AudioManager::instance()->playBGM();
PhysicsManager& PhysicsManager::Instance()
{
	// TODO to refernece, can never be nullptr (should never)
	static PhysicsManager sInstance; // Guaranteed to be destroyed.
								   // Instantiated on first use.

	return sInstance;
}

bool PhysicsManager::checkCollision(float midX, float midY, float radius)
{
	bool isCollision = false;
	for (int i = 0; i < collidables->size(); i++) {
		int xStep = midX - collidables->at(i).getMidX();
		int yStep = midY - collidables->at(i).getMidY();
		int collisionRange =radius + collidables->at(i).getRadius();


		int distance = sqrt((xStep*xStep) + (yStep*yStep));

		if (distance < 0) {
			distance *= -1;
		}

		if (distance < collisionRange) {
			isCollision = true;
		}
	}

	return isCollision;
}

