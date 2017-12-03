//
// Created by Ahmad Rahimi on 12/3/17.
//

#include "QuadTree.h"
using namespace std;
QuadTree::QuadTree(int level, SDL_Rect bounds) : level(level), bounds(bounds) {

}

void QuadTree::ClearNode(){
    objects.clear();

    for (int i = 0; i < nodes.size(); i++) {
        nodes.at(i).ClearNode();
    }
}

void QuadTree::CreateSubNodes() {
    SDL_Rect subBounds = SDL_Rect();
    subBounds.x = this->bounds.x;
    subBounds.y = this->bounds.x;
    subBounds.w = this->bounds.w / 2;
    subBounds.h = this->bounds.h / 2;
    int nextLevel = level+1;
    nodes.emplace_back(nextLevel, subBounds.x, subBounds.y, subBounds.w, subBounds.h);
    nodes.emplace_back(nextLevel, subBounds.x + subBounds.w, subBounds.y, subBounds.w, subBounds.h);
    nodes.emplace_back(nextLevel, subBounds.x, subBounds.y + subBounds.h, subBounds.w, subBounds.h);
    nodes.emplace_back(nextLevel, subBounds.x + subBounds.w, subBounds.y + subBounds.h, subBounds.w, subBounds.h);
}

QuadTree::QuadTree(int level, int x, int y, int w, int h) : level(level){
    this->bounds = SDL_Rect();
    bounds.x = x;
    bounds.y = y;
    bounds.w = w;
    bounds.y = y;
}

int QuadTree::getIndex(SDL_Rect objectBounds) const {
    int index = -1;
    //visa versa??
    double midY = this->bounds.y + (bounds.h/2);
    double midX = this->bounds.x + (bounds.w/2);

    bool topQuad = (objectBounds.y < midY && (objectBounds.y + objectBounds.h) < midY);
    bool botQuad = (objectBounds.y > midY);

    //object past in linker kwadraten
    if(objectBounds.x < midX && (objectBounds.x + objectBounds.w) < midX) {
        if(topQuad){
            index = 0;
        }else if(botQuad){
            index = 2;
        }
    }else {
        if(topQuad){
            index = 1;
        }else if(botQuad){
            index = 3;
        }
    }
    return index;
}

void QuadTree::Insert(GameObject gameObject) {
    SDL_Rect rect = gameObject.GetRect();
    if(this->nodes.size() != 0) {
        int index = getIndex(rect);
    }
    objects.push_back(gameObject);
    if(objects.size() > MAX_OBJECTS && level < MAX_LEVEL){
        if(this->nodes.size() == 0) {
            this->CreateSubNodes();
        }

        int i = 0;
        while(i < objects.size()) {
            int index = getIndex(objects.at(i).GetRect());
            if (index != -1) {
                this->nodes.at(index).Insert(objects.at(i));
                this->objects.erase(objects.begin() + i);
            } else {
                i++;
            };
        }
    }
}

std::vector<GameObject> QuadTree::Retrieve(SDL_Rect rect) const {
    int index = this->getIndex(rect);
    if (index != -1 && this->nodes.size() != 0) {
        std::vector<GameObject> otherNodessObjects;
        std::vector<GameObject> currentNodesObjects;
        otherNodessObjects = nodes[index].Retrieve(rect);
        currentNodesObjects.reserve( currentNodesObjects.size() + otherNodessObjects.size() );
        currentNodesObjects.insert(currentNodesObjects.end(), otherNodessObjects.begin(), otherNodessObjects.end());
        return currentNodesObjects;
    }else{
        return objects;
    }
}

QuadTree::QuadTree() = default;
