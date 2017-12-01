//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "Flock.h"

Flock::Flock(shared_ptr<EnemyBase> leader) {
    this->leader = leader;
    //this->members.push_back(leader);
    mapW = MapManager::Instance().getTmx().mapInfo.width * MapManager::Instance().getTmx().mapInfo.tileWidth;
    mapH = MapManager::Instance().getTmx().mapInfo.height * MapManager::Instance().getTmx().mapInfo.tileHeight;

    for(int x = 0; x <= mapW/32; x++){
        for(int y = 0; y <= mapH/32; y++){
            std::vector<EnemyBase> ebVector;
            this->quadtree[std::to_string(x) + std::to_string(y)] = ebVector;
        }
    }
}

void Flock::addMember(EnemyBase newMember) {
    newMember.setLeader(leader);
    newMember.setTarget(leader->getTarget());
    this->members.push_back(newMember);

}

void Flock::removeFarMembers() {
//todo alle members die ver weg zijn worden geremoved
}
//
void updateEnemyMapping(){
}

void Flock::update(float time) {
    //todo een manier vinden om alleen objecten mee te sturen die in de buurt zijn
    leader->updatePositions(members, time);
    for (auto &member: this->members) {
        auto test = this->quadtree[member.currentQuadrant];
        member.updatePositions(this->quadtree[member.currentQuadrant], time);
        member.currentQuadrant = this->placeEnemyAtQuadrant(member);
    }

//    map<string, std::vector<EnemyBase>>::iterator it;
//    cout << "-----------" << endl;
//    for ( it = this->quadtree.begin(); it != this->quadtree.end(); it++ )
//    {
//        if(it->second.size() > 0) {
//            cout << it->first << endl;
//            cout << it->second.size() << endl;
//        }
//    }
//    cout << "-----------" << endl;
}

void Flock::draw() {
    leader->draw();
    for (auto &member: this->members) {
        member.draw();
    }
}

string Flock::placeEnemyAtQuadrant(EnemyBase& replaceEnemy) {
    int qW = int(replaceEnemy.GetCoordinates().x) / 32;
    int qH = int(replaceEnemy.GetCoordinates().y) / 32;
    string nextPos = std::to_string(qW) + std::to_string(qH);
    if(nextPos != replaceEnemy.currentQuadrant) {
        if(replaceEnemy.currentQuadrantIndex != -1) {
            auto it = std::find(this->quadtree[replaceEnemy.currentQuadrant].begin(), this->quadtree[replaceEnemy.currentQuadrant].end(), replaceEnemy);
            if(it != this->quadtree[replaceEnemy.currentQuadrant].end()) {
                this->quadtree[replaceEnemy.currentQuadrant].erase(it);
               // cout << " deleted!" << endl;
            }
        }
        this->quadtree[nextPos].push_back(replaceEnemy);
        replaceEnemy.currentQuadrant = nextPos;
        replaceEnemy.currentQuadrantIndex = this->quadtree[nextPos].size();
    }
    return replaceEnemy.currentQuadrant;
}
