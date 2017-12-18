#include "PhysicsManager.h"
#include <cmath>
#include "../Game/Config.h"

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
		m->onBaseCollision(true);
	}

}

bool PhysicsManager::IntersectsRect(float midX, float midY, float radius, const GameObject* collidable)
{
	Point circleDistance;
	circleDistance.x = abs(midX - collidable->getMidX());
	circleDistance.y = abs(midY - collidable->getMidY());

	if (circleDistance.x >(collidable->getWidth() / 2 + radius)) { return false; }
	if (circleDistance.y > (collidable->getHeight() / 2 + radius)) { return false; }

	if (circleDistance.x <= (collidable->getWidth() /2) ) { return true; }
	if (circleDistance.y <= (collidable->getHeight() /2)) { return true; }

	int cornerDistance_sq = pow(circleDistance.x - collidable->getWidth() / 2, 2) +
		pow(circleDistance.y - collidable->getHeight() / 2, 2);

	return (cornerDistance_sq <= radius * radius);
}

bool PhysicsManager::IntersectsCircle(float midX, float midY, float radius, const MoveableObject* collidable)
{
	Point circleDistance;
	circleDistance.x = abs(midX - collidable->getMidX());
	circleDistance.y = abs(midY - collidable->getMidY());

	if (circleDistance.x >(collidable->getWidth() / 2 + radius)) { return false; }
	if (circleDistance.y > (collidable->getHeight() / 2 + radius)) { return false; }

	if (circleDistance.x <= (collidable->getWidth() / 2)) { return true; }
	if (circleDistance.y <= (collidable->getHeight() / 2)) { return true; }

	return (false);
}

void PhysicsManager::checkStaticObjectCollision(MoveableObject* m, Point newPos)
{
	bool isCollision = false;
	auto midX = m->getPredictionMidX(newPos.x);
	auto midY = m->getPredictionMidY(newPos.y);
	auto radius = m->getRadius();
	for (int i = 0; i < collidables->size(); i++) {
		if (IntersectsRect(midX, midY, radius, &collidables->at(i))) {
			m->onBaseCollision(true);
		}
	}
}

void PhysicsManager::checkMoveableCollision(MoveableObject* m, Point newPos)
{
	auto midX = m->getPredictionMidX(newPos.x);
	auto midY = m->getPredictionMidY(newPos.y);
	auto radius = m->getRadius();


	for (int i = 0; i < objects->size(); i++) {
		if (IntersectsCircle(midX, midY, radius, objects->at(i).get())) {
			m->onBaseCollision(objects->at(i).get());
			break;
		}
	}
}

void PhysicsManager::setStaticObjects()
{
	if (collidables == NULL) {
		collidables = MapManager::Instance().getCollidables();
	}
	_tileSize = config::tileSize;
	_playScreenWidth = config::width - _tileSize;
	_playScreenHeight = config::height - _tileSize;
}

void PhysicsManager::setMoveableObjects(vector<shared_ptr<MoveableObject>>* _objs)
{
	objects = _objs;
}


void PhysicsManager::CheckQuadTreeCollision(MoveableObject* m, Point newPos) {
	std::vector<GameObject> nearbyObjects = RetrieveNearbyGameObjects(*m);

	auto midX = m->getPredictionMidX(newPos.x);
	auto midY = m->getPredictionMidY(newPos.y);
	auto radius = m->getRadius();

	for (int i = 0; i < nearbyObjects.size(); i++) {

		int xStep = midX - nearbyObjects.at(i).getMidX();
		int yStep = midY - nearbyObjects.at(i).getMidY();
		int collisionRange = radius + nearbyObjects.at(i).getRadius();
		int distance = sqrt((xStep*xStep) + (yStep*yStep));

		if (distance < 0) {
		distance *= -1;
		}

		if (distance < collisionRange) {
			m->onBaseCollision(nearbyObjects.at(i));
			break;
		}
	}
}


const vector<GameObject>* PhysicsManager::getCollidables()
{
	return collidables;
}

void PhysicsManager::UpdateQuadTree(std::vector<GameObject> &gameObjects) {
	this->_quadtree = QuadTree(0, MapManager::Instance().GetMapRect());
	for (auto& gameObject : *MapManager::Instance().getCollidables()) {
		_quadtree.Insert(gameObject);
	}
	for (const auto& gameObject : gameObjects) {
		_quadtree.Insert(gameObject);
	}
}

void PhysicsManager::UpdateQuadTree(std::vector<shared_ptr<GameObject>> &gameObjects) {
	this->_quadtree.ClearNode();
	this->_quadtree = QuadTree(0, MapManager::Instance().GetMapRect());
	for (auto& gameObject : *MapManager::Instance().getCollidables()) {
		_quadtree.Insert(gameObject);
	}
	for (const auto& gameObject : gameObjects) {
		_quadtree.Insert(*gameObject.get());
	}
}

const QuadTree &PhysicsManager::GetQuadTree() const {
	return _quadtree;
}

void PhysicsManager::DrawQTree() {
	this->_quadtree.Draw();
}

std::vector<GameObject> PhysicsManager::RetrieveNearbyGameObjects(GameObject &gameObject) {
	return this->_quadtree.Retrieve(gameObject.GetRect());
}


