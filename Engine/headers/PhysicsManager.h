#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <math.h>
#include "MapManager.h"
#include "GameObject.h"
#include <string>
#include "AssetManager.h"
#include <memory>
#include <Point.h>

class MoveableObject;
class PhysicsManager {
public:
	PhysicsManager(PhysicsManager const&) = delete;
	void operator=(PhysicsManager const&) = delete;

	PhysicsManager();
	~PhysicsManager();

	static PhysicsManager& Instance();
	void checkWallCollision(MoveableObject* m, Point newPos);
	bool checkStaticObjectCollision(float midX, float midY, float radius); 
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
};
#endif
