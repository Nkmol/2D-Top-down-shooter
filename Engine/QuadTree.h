//
// Created by Ahmad Rahimi on 12/3/17.
//

#ifndef SHOOTER_QUADTREE_H
#define SHOOTER_QUADTREE_H

#include <SDL_rect.h>
#include "GameObject.h"
#include "vector"
class QuadTree {
private:
    int MAX_OBJECTS = 50, MAX_LEVEL = 100, level;
    std::vector<GameObject> objects;
    SDL_Rect bounds;
    std::vector<QuadTree> nodes;
    int getIndex(SDL_Rect objectBounds) const;

public:
    QuadTree(int level, SDL_Rect bounds);
    QuadTree(int level, int x, int y, int w, int h);

    QuadTree();

    void ClearNode();
    void CreateSubNodes();
    //for debug purposes
    void Draw();
    void Insert(GameObject gameObject);
    std::vector<GameObject> Retrieve(SDL_Rect rect) const;
};


#endif //SHOOTER_QUADTREE_H
