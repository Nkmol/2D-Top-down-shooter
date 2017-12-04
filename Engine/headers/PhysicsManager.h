#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <math.h>
#include "MapManager.h"
#include "GameObject.h"
#include "MoveableObject.h"
#include <string>
#include "AssetManager.h"
#include "../QuadTree.h"

using namespace std;

class PhysicsManager {
public:
	PhysicsManager(PhysicsManager const&) = delete;
	void operator=(PhysicsManager const&) = delete;

	PhysicsManager();
	~PhysicsManager();

	static PhysicsManager& Instance();
	const std::vector<GameObject>* collidables;
	bool checkCollision(float midX, float midY, float radius);
	void UpdateQuadTree(std::vector<GameObject> gameObjects);
	void UpdateQuadTree(std::vector<shared_ptr<GameObject>> gameObjects);
	const QuadTree &GetQuadTree() const;
	void DrawQTree();
private:
	float _tileSize;
	float _playScreenWidth;
	float _playScreenHeight;
	QuadTree _quadtree;

};
#endif
