#include "PhysicsManager.h"
#include <cmath>

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
	if (checkStaticObjectCollision(midX, midY, radius)) {
		m->onBaseCollision(true);
	}
}

bool intersects(float midX, float midY, float radius, const GameObject* collidable)
{
	Point circleDistance;
	circleDistance.x = abs(midX - collidable->GetCoordinates().x);
	circleDistance.y = abs(midY - collidable->GetCoordinates().y);

	if (circleDistance.x >(collidable->getWidth() / 2 + radius)) { return false; }
	if (circleDistance.y > (collidable->getHeight() / 2 + radius)) { return false; }

	if (circleDistance.x <= (collidable->getWidth() / 2)) { return true; }
	if (circleDistance.y <= (collidable->getHeight() / 2)) { return true; }

	int cornerDistance_sq = pow(circleDistance.x - collidable->getWidth() / 2, 2) +
		pow(circleDistance.y - collidable->getHeight() / 2, 2);

	return (cornerDistance_sq <= radius * radius);
}

bool PhysicsManager::checkStaticObjectCollision(float midX, float midY, float radius)
{
	bool isCollision = false;

	for (int i = 0; i < collidables->size(); i++) {
		//int xStep = midX - collidables->at(i).getMidX();
		//int yStep = midY - collidables->at(i).getMidY();
		//int collisionRange = radius + collidables->at(i).getRadius();



		//// Find the closest point to the circle within the rectangle
		//float closestX = clamp(midX, , collidables->at(i).GetCoordinates().x + collidables->at(i).getWidth());
		//float closestY = clamp(midY, collidables->at(i).GetCoordinates().y, collidables->at(i).GetCoordinates().y + collidables->at(i).getHeight());

		//// Calculate the distance between the circle's center and this closest point
		//float distanceX = midX - closestX;
		//float distanceY = midY - closestY;



		// If the distance is less than the circle's radius, an intersection occurs
		//float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

		if (intersects(midX, midY, radius, &collidables->at(i))) {
			isCollision = true;
			break;
		}
	}

			return isCollision;
	}



	//	int distance = sqrt((xStep*xStep) + (yStep*yStep));

	//	if (distance < 0) {
	//		distance *= -1;
	//	}

	//	if (distance < collisionRange) {
	//		isCollision = true;
	//		break;
	//	}
	//}

	//return isCollision;


void PhysicsManager::checkMoveableCollision(MoveableObject* m, Point newPos)
{
	auto midX = m->getPredictionMidX(newPos.x);
	auto midY = m->getPredictionMidY(newPos.y);
	auto radius = m->getRadius();

	for (int i = 0; i < objects->size(); i++) {

		int xStep = midX - objects->at(i).get()->getMidX();
		int yStep = midY - objects->at(i).get()->getMidY();
		int collisionRange = radius + objects->at(i).get()->getRadius();
		int distance = sqrt((xStep*xStep) + (yStep*yStep));

		if (distance < 0) {
			distance *= -1;
		}

		if (distance < collisionRange) {
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
	_tileSize = 32;
	_playScreenWidth = 39 * _tileSize;
	_playScreenHeight = 29 * _tileSize;
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
		//int distance = sqrt((xStep*xStep) + (yStep*yStep));

		//if (distance < 0) {
		//distance *= -1;
		//}

		if (0> collisionRange) {
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


