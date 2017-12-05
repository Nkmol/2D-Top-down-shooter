#include "PhysicsManager.h"
#include "MoveableObject.h"

PhysicsManager::PhysicsManager()
{

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

bool PhysicsManager::checkOuterWallCollision(float midX, float midY, float radius)
{
	bool isCollision = false;
	if (midX - radius < _tileSize || midY - radius < _tileSize || midX + radius > _playScreenWidth || midY + radius > _playScreenHeight) {
		return true;
	}



	return checkStaticObjectCollision(midX, midY, radius);
}


bool PhysicsManager::checkStaticObjectCollision(float midX, float midY, float radius)
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
			break;
		}
	}

	return isCollision;
}

bool PhysicsManager::checkMoveableCollision(float midX, float midY, float radius)
{
	bool isCollision = false;

	//for (int i = 0; i < objects.size(); i++) {
	//	int xStep = midX - objects.at(i).getMidX();
	//	int yStep = midY - objects.at(i).getMidY();
	//	int collisionRange = radius + collidables->at(i).getRadius();


	//	int distance = sqrt((xStep*xStep) + (yStep*yStep));

	//	if (distance < 0) {
	//		distance *= -1;
	//	}

	//	if (distance < collisionRange) {
	//		isCollision = true;
	//		break;
	//	}
	//}

	return isCollision;
}

void PhysicsManager::setStaticObjects()
{
	if (collidables == NULL) {
		collidables = MapManager::Instance().getCollidables();
	}
	_tileSize = collidables->at(0).getRadius() * 2;
	_playScreenWidth = 39 * _tileSize;
	_playScreenHeight = 29 * _tileSize;
}

void PhysicsManager::setMoveableObjects(vector<shared_ptr<MoveableObject>>* _objs)
{
	objects = _objs;
}



const vector<GameObject>* PhysicsManager::getCollidables()
{
	return collidables;
}

