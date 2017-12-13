#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <math.h>
#include "MapManager.h"
#include "GameObject.h"
#include <string>
#include "AssetManager.h"
#include <memory>
#include <Point.h>
#include "../QuadTree.h"
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
	const std::vector<GameObject>* collidables;
    std::vector<reference_wrapper<const GameObject>> RetrieveNearbyGameObjects(GameObject &gameObject);

	void checkWallCollision(MoveableObject* m, Point newPos);

	bool checkStaticObjectCollision(float midX, float midY, float radius);
	void checkMoveableCollision(MoveableObject* m, Point newPos);
	void setStaticObjects();
	void setMoveableObjects(vector<shared_ptr<MoveableObject>>* _objs);
	void CheckQuadTreeCollision(MoveableObject * m, Point newPos);
	const vector<GameObject>* getCollidables();
	void UpdateQuadTree(std::vector<shared_ptr<GameObject>> &gameObjects);
	const QuadTree &GetQuadTree() const;
	void DrawQTree();

private:
	std::vector<shared_ptr<MoveableObject>>* objects;
	float _tileSize;
	float _playScreenWidth;
	float _playScreenHeight;
	QuadTree _quadtree;
	bool IntersectsRect(float midX, float midY, float radius, const GameObject * collidable);
	bool IntersectsCircle(float midX, float midY, float radius, const MoveableObject * collidable);

};

template<class T>
const T& clamp(const T& x, const T& upper, const T& lower) {
	return std::min(upper, max(x, lower));
}

#endif
