#include "PhysicsManager.h"


PhysicsManager::PhysicsManager()
{
	if(collidables == NULL){}
		collidables = MapManager::Instance().getCollidables();
	_tileSize = collidables->at(0).getRadius() * 2;
	_playScreenWidth = 39 * _tileSize;
	_playScreenHeight = 29 * _tileSize;
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
	if (midX - radius < _tileSize ) {
		return true;
	}

	if (midY - radius < _tileSize) {
		return true;
	}

	if (midX + radius > _playScreenWidth) {
		return true;
	}

	if (midY + radius > _playScreenHeight) {
		return true;
	}
	
	//for (int i = 0; i < collidables->size(); i++) {
	//	int xStep = midX - collidables->at(i).getMidX();
	//	int yStep = midY - collidables->at(i).getMidY();
	//	int collisionRange =radius + collidables->at(i).getRadius();


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

void PhysicsManager::UpdateQuadTree(std::vector<GameObject> gameObjects) {
	this->_quadtree = QuadTree(0, MapManager::Instance().GetMapRect());
	for (const auto& gameObject: gameObjects) {
		_quadtree.Insert(gameObject);
	}
}

void PhysicsManager::UpdateQuadTree(std::vector<shared_ptr<GameObject>> gameObjects) {
	this->_quadtree.ClearNode();
	this->_quadtree = QuadTree(0, MapManager::Instance().GetMapRect());
	for (const auto& gameObject: gameObjects) {
		_quadtree.Insert(*gameObject.get());
	}
}

const QuadTree &PhysicsManager::GetQuadTree() const {
	return _quadtree;
}

