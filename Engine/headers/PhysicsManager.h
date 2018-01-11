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

	void CheckNewStaticObjectCollision(MoveableObject * m, Point newPos);
	void CheckWallCollision(MoveableObject* m, Point newPos);
	void CheckStaticObjectCollision(MoveableObject* m, Point newPos);
	void CheckMoveableCollision(MoveableObject* m, Point newPos);
	void SetStaticObjects();
	void SetMoveableObjects(vector<shared_ptr<MoveableObject>>* _objs);
	const vector<GameObject>* GetCollidables();
private:
	std::vector<shared_ptr<MoveableObject>>* _objects;
	const std::vector<GameObject>* _collidables;
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
