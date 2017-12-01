#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <math.h>
#include "MapManager.h"
#include "GameObject.h"
#include "MoveableObject.h"
#include <string>
#include "AssetManager.h"

using namespace std;

class PhysicsManager {
public:
	PhysicsManager(PhysicsManager const&) = delete;
	void operator=(PhysicsManager const&) = delete;

	PhysicsManager();
	~PhysicsManager();

	static PhysicsManager& Instance();
	const std::vector<GameObject>* collidables;
	bool checkOuterWallCollision(float midX, float midY, float radius); 
	bool checkStaticObjectCollision(float midX, float midY, float radius); 
	bool checkMoveableCollision(float midX, float midY, float radius);
private:
	float _tileSize;
	float _playScreenWidth;
	float _playScreenHeight;
};
#endif
