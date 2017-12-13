//
// Created by Ahmad Rahimi on 12/3/17.
//

#include <SDL_system.h>
#include <RenderManager.h>
#include "QuadTree.h"
using namespace std;
QuadTree::QuadTree(int level, SDL_Rect bounds) : level(level), bounds(bounds) {
//    int woffset = bounds.w/4;
//    int hoffset = bounds.h/4;

//    this->bounds.x -= woffset;
//    this->bounds.y -= hoffset;
//    this->bounds.w += woffset*2;
//    this->bounds.h += hoffset*2;
}

void QuadTree::ClearNode(){
    objects.clear();

    for (auto &node : nodes) {
        node.ClearNode();
    }
}

void QuadTree::CreateSubNodes() {
    SDL_Rect subBounds = SDL_Rect();
    subBounds.x = this->bounds.x;
    subBounds.y = this->bounds.y;
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
    int woffset = w/4;
    int hoffset = h/4;
    bounds.x = x-woffset;
    bounds.y = y-hoffset;
    bounds.w = w+(woffset*2);
    bounds.h = h+(hoffset*2);
}

std::vector<int> QuadTree::getIndex(SDL_Rect objectBounds) const {
    std::vector<int> indexes;

    double midY = this->bounds.y + (bounds.h/2);
    double midX = this->bounds.x + (bounds.w/2);

    bool topQuad = (objectBounds.y < midY);
    bool botQuad = ((objectBounds.y + objectBounds.h) > midY);

    //object past in linker kwadraten
    if(objectBounds.x < midX) {
        if(topQuad){
            indexes.emplace_back(0);
        }
        if(botQuad){
            indexes.emplace_back(2);
        }
    //object past in rechter kwadraten
    } if((objectBounds.x + objectBounds.w) > midX) {
        if(topQuad){
            indexes.emplace_back(1);
        }
        if(botQuad){
            indexes.emplace_back(3);
        }
    }
    return indexes;
}

//void QuadTree::Insert(std::reference_wrapper<GameObject> gameObject) {
//    SDL_Rect rect = gameObject.get().GetRect();
//    if(this->nodes.size() != 0) {
//        int index = getIndex(rect);
//    }
//    objects.push_back(const gameObject);
//    if(objects.size() > MAX_OBJECTS && level < MAX_LEVEL){
//        if(this->nodes.size() == 0) {
//            this->CreateSubNodes();
//        }
//
//        int i = 0;
//        while(i < objects.size()) {
//            int index = getIndex(objects.at(i).get().GetRect());
//            if (index != -1) {
//                this->nodes.at(index).Insert(objects.at(i));
//                this->objects.erase(objects.begin() + i);
//            } else {
//                i++;
//            };
//        }
//    }
//}

void QuadTree::Insert(std::reference_wrapper<GameObject> gameObject) {
    SDL_Rect rect = gameObject.get().GetRect();
    if(this->nodes.size() != 0) {
        vector<int> indexes = getIndex(rect);
        if(!indexes.empty()) {
            for (int &index: indexes) {
                nodes.at(index).Insert(gameObject);
            }
            return;
        }
    }
    objects.push_back(gameObject);
    if(objects.size() > MAX_OBJECTS && level < MAX_LEVEL){
        if(this->nodes.size() == 0) {
            this->CreateSubNodes();
        }

        int i = 0;
        while(i < objects.size()) {
            if(objects.size() == 0){
                cout << "weird" << endl;
            }
            bool didAdd = false;
            vector<int> indexes = getIndex(rect);
            if(!indexes.empty()) {
                for (int &index: indexes) {
                    this->nodes.at(index).Insert(objects.at(i));
                    didAdd = true;
                }
                if(didAdd){
                    this->objects.erase(objects.begin() + i);
                }
            }else{
                i++;
            }
        }
    }else{
        if(gameObject.get().GetTeamId() != -100) { // -100 == collidables
            gameObject.get().setNearbyObjects(objects);
            for(auto object : objects){
                object.get().setNearbyObjects(objects);
            }
        }
    }
}

vector<reference_wrapper<GameObject>> QuadTree::Retrieve(SDL_Rect rect) {
    vector<int> indexes = this->getIndex(rect);
    if (!indexes.empty() && this->nodes.size() != 0) {
        vector<reference_wrapper<GameObject>> resultObjects;
        for(int& index: indexes){
            vector<reference_wrapper<GameObject>> nodeObjects = this->nodes.at(index).Retrieve(rect);
            resultObjects.insert(resultObjects.end(), nodeObjects.begin(), nodeObjects.end());
        }
        return resultObjects;
        //mergen is tijdrovend!
        //currentNodesObjects.reserve( currentNodesObjects.size() + otherNodessObjects.size() );
        //currentNodesObjects.insert(currentNodesObjects.end(), otherNodesObjects.begin(), otherNodesObjects.end());
    }
    return objects;

}

void QuadTree::Draw(){
    SDL_SetRenderDrawColor(RenderManager::Instance().GetRenderer(), 255, 0, 0, 50);
    SDL_RenderDrawRect(RenderManager::Instance().GetRenderer(), &bounds);

    RenderManager::Instance().DrawText(to_string(this->objects.size()), this->bounds.x + this->bounds.w / 2,
                                       this->bounds.y + this->bounds.h / 2, 30, 15, 0);
    if(level == 0) {
        double midY = this->bounds.y + (bounds.h / 2);
        SDL_SetRenderDrawColor(RenderManager::Instance().GetRenderer(), 255, 0, 0, 255);
        SDL_RenderDrawLine(RenderManager::Instance().GetRenderer(), 0, midY, 1000, midY);
    }
    for(int i = 0; i < nodes.size(); i++){
       nodes.at(i).Draw();//nodes.at(2).Draw();
    }
    SDL_SetRenderDrawColor(RenderManager::Instance().GetRenderer(), 0, 0, 0, 0);
}

QuadTree::QuadTree() = default;
