//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "Flock.h"

Flock::Flock(unique_ptr<EnemyBase> leader) : _leader(*leader)
{
	_members.push_back(move(leader));
  mapW = MapManager::Instance().getTmx().mapInfo.width * MapManager::Instance().getTmx().mapInfo.tileWidth;
  mapH = MapManager::Instance().getTmx().mapInfo.height * MapManager::Instance().getTmx().mapInfo.tileHeight;

  for(int x = 0; x <= mapW/32; x++){
      for(int y = 0; y <= mapH/32; y++){
          std::vector<EnemyBase> ebVector;
          this->quadtree[std::to_string(x) + std::to_string(y)] = ebVector;
      }
  }
}

void Flock::AddMember(unique_ptr<EnemyBase> newMember)
{
	newMember->setLeader(_leader);
	newMember->setTarget(_leader.getTarget());
	_members.push_back(move(newMember));
}

void Flock::RemoveFarMembers()
{
	//todo alle members die ver weg zijn worden geremoved
}
//
void updateEnemyMapping(){
}

void Flock::Update(const float time)
{
	//todo een manier vinden om alleen objecten mee te sturen die in de buurt zijn
  leader->updatePositions(members, time);
  for (auto const &member: this->members) {
      auto test = this->quadtree[member.currentQuadrant];
      member.updatePositions(this->quadtree[member.currentQuadrant], time);
      member.currentQuadrant = this->placeEnemyAtQuadrant(member);
  }
}

void Flock::Draw()
{
	for (auto const& member : _members)
	{
		member->draw();
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
