#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <math.h>
#include "MapManager.h"
#include "GameObject.h"
#include <string>
#include "AssetManager.h"
#include <memory>
#include <Point.h>
#include "MoveableObject.h"
#include <algorithm>


class MoveableObject;
class gameObject;
class PhysicsManager {
public:
	PhysicsManager(PhysicsManager const&) = delete;
	void operator=(PhysicsManager const&) = delete;

	PhysicsManager();
	~PhysicsManager();

	static PhysicsManager& Instance();

	void checkWallCollision(MoveableObject* m, Point newPos);
	void checkStaticObjectCollision(MoveableObject* m, Point newPos);
	void checkNewStaticObjectCollision(MoveableObject * m, Point newPos);
	void checkMoveableCollision(MoveableObject* m, Point newPos);
	void setStaticObjects();
	void setMoveableObjects(vector<shared_ptr<MoveableObject>>* _objs);
	const vector<GameObject>* getCollidables();
private:
	std::vector<shared_ptr<MoveableObject>>* objects;
	const std::vector<GameObject>* collidables;
	float _tileSize;
	float _playScreenWidth;
	float _playScreenHeight;
	bool IntersectsRect(float midX, float midY, float radius, const GameObject * collidable);
	bool IntersectsCircle(float midX, float midY, float radius, const MoveableObject * collidable);

};

template<class T>
const T& clamp(const T& x, const T& upper, const T& lower) {
	return std::min(upper, max(x, lower));
}

#endif
