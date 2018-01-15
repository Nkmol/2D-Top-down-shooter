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
	static PhysicsManager _instance; // Guaranteed to be destroyed.
									 // Instantiated on first use.

	return _instance;
}

void PhysicsManager::CheckWallCollision(MoveableObject* m, Point newPos)
{
	bool isCollision = false;
	auto midX = m->GetPredictionMidX(newPos.x);
	auto midY = m->GetPredictionMidY(newPos.y);
	auto radius = m->GetRadius();

	if (midX - radius < 0 || midY - radius < 0 || midX + radius > _playScreenWidth || midY + radius > _playScreenHeight) {
		m->OnBaseCollision(true);
	}

}

bool PhysicsManager::IntersectsRect(float midX, float midY, float radius, const GameObject* collidable)
{
	Point circleDistance;
	circleDistance.x = abs(midX - collidable->GetMidX());
	circleDistance.y = abs(midY - collidable->GetMidY());

	if (circleDistance.x >(collidable->GetWidth() / 2 + radius)) { return false; }
	if (circleDistance.y > (collidable->GetHeight() / 2 + radius)) { return false; }

	if (circleDistance.x <= (collidable->GetWidth() /2) ) { return true; }
	if (circleDistance.y <= (collidable->GetHeight() /2)) { return true; }

	int cornerDistance_sq = pow(circleDistance.x - collidable->GetWidth() / 2, 2) +
		pow(circleDistance.y - collidable->GetHeight() / 2, 2);

	return (cornerDistance_sq <= radius * radius);
}

bool PhysicsManager::IntersectsCircle(float midX, float midY, float radius, const MoveableObject* collidable)
{
	Point circleDistance;
	circleDistance.x = abs(midX - collidable->GetMidX());
	circleDistance.y = abs(midY - collidable->GetMidY());

	if (circleDistance.x >(collidable->GetWidth() / 2 + radius)) { return false; }
	if (circleDistance.y > (collidable->GetHeight() / 2 + radius)) { return false; }

	if (circleDistance.x <= (collidable->GetWidth() / 2)) { return true; }
	if (circleDistance.y <= (collidable->GetHeight() / 2)) { return true; }

	return (false);
}
//
//void PhysicsManager::CheckStaticObjectCollision(MoveableObject* m, Point newPos)
//{
//	bool isCollision = false;
//
//	auto midX = m->GetPredictionMidX(newPos.x);
//	auto midY = m->GetPredictionMidY(newPos.y);
//	auto radius = m->GetRadius();
//	for (int i = 0; i < _collidables->size(); i++) {
//		if (IntersectsRect(midX, midY, radius, &_collidables->at(i))) {
//			m->OnBaseCollision(true);
//			break;
//		}
//	}
//}

void PhysicsManager::CheckNewStaticObjectCollision(MoveableObject* m, Point newPos)
{
	bool isCollision = false;
	auto midX = m->GetPredictionMidX(newPos.x);
	auto midY = m->GetPredictionMidY(newPos.y);
	auto radius = m->GetRadius();
	std::vector<GameObject*> tmep = {};
	MapManager::Instance().getNearbyCollidables(newPos, &tmep);
	for (int i = 0; i < tmep.size(); i++) {
		if (IntersectsRect(midX, midY, radius, tmep.at(i))) {
			m->OnBaseCollision(true);
			break;
		}
	}
}

void PhysicsManager::CheckMoveableCollision(MoveableObject* m, Point newPos)
{
	auto midX = m->GetPredictionMidX(newPos.x);
	auto midY = m->GetPredictionMidY(newPos.y);
	auto radius = m->GetRadius();


	for (int i = 0; i < _objects->size(); i++) {
		if (IntersectsCircle(midX, midY, radius, _objects->at(i).get())) {
			m->OnBaseCollision(_objects->at(i).get());
			break;
		}
	}
}

void PhysicsManager::SetStaticObjects()
{
	if (_collidables == NULL) {
		//_collidables = MapManager::Instance().GetCollidables();
	}
	_tileSize = config::tileSize;
	_playScreenWidth = config::width;
	_playScreenHeight = config::height;
}

void PhysicsManager::SetMoveableObjects(vector<shared_ptr<MoveableObject>>* _objs)
{
	_objects = _objs;
}

const vector<GameObject>* PhysicsManager::GetCollidables()
{
	return _collidables;
}
