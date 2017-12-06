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

void PhysicsManager::checkWallCollision(MoveableObject* m, Point newPos)
{
	bool isCollision = false;
	auto midX = m->getPredictionMidX(newPos.x);
	auto midY = m->getPredictionMidY(newPos.y);
	auto radius = m->getRadius();

	if (midX - radius < _tileSize || midY - radius < _tileSize || midX + radius > _playScreenWidth || midY + radius > _playScreenHeight) {
		m->onCollision(true);
	}
	if (checkStaticObjectCollision(midX, midY, radius)) {
		m->onCollision(true);
	}
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

void PhysicsManager::checkMoveableCollision(MoveableObject* m, Point newPos)
{
	auto midX = m->getPredictionMidX(newPos.x);
	auto midY = m->getPredictionMidY(newPos.y);
	auto radius = m->getRadius();

	for (int i = 0; i < objects->size(); i++){
		
		int xStep = midX - objects->at(i).get()->getMidX();
		int yStep = midY - objects->at(i).get()->getMidY();
		int collisionRange = radius + objects->at(i).get()->getRadius();
		int distance = sqrt((xStep*xStep) + (yStep*yStep));

		if (distance < 0) {
			distance *= -1;
		}

		if (distance < collisionRange) {
			m->onBaseCollision(objects->at(i));
			break;
		}
	}
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

void PhysicsManager::UpdateQuadTree(std::vector<GameObject> &gameObjects) {
	this->_quadtree = QuadTree(0, MapManager::Instance().GetMapRect());
	for (auto& gameObject: *MapManager::Instance().getCollidables()) {
		_quadtree.Insert(gameObject);
	}
	for (const auto& gameObject: gameObjects) {
		_quadtree.Insert(gameObject);
	}
}

void PhysicsManager::UpdateQuadTree(std::vector<shared_ptr<GameObject>> &gameObjects) {
	this->_quadtree.ClearNode();
	this->_quadtree = QuadTree(0, MapManager::Instance().GetMapRect());
	for (auto& gameObject: *MapManager::Instance().getCollidables()) {
		_quadtree.Insert(gameObject);
	}
	for (const auto& gameObject: gameObjects) {
		_quadtree.Insert(*gameObject.get());
	}
}

const QuadTree &PhysicsManager::GetQuadTree() const {
	return _quadtree;
}

void PhysicsManager::DrawQTree(){
	this->_quadtree.Draw();
}

std::vector<GameObject> PhysicsManager::RetrieveNearbyGameObjects(GameObject &gameObject) {
	return this->_quadtree.Retrieve(gameObject.GetRect());
}
