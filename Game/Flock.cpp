//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "Flock.h"

Flock::Flock(shared_ptr<EnemyBase> leader) {
    this->leader = leader;
    this->members.push_back(leader);
}

void Flock::addMember(shared_ptr<EnemyBase> newMember) {
    newMember->setLeader(leader);
    newMember->setTarget(leader->getTarget());
    this->members.push_back(newMember);
}

void Flock::removeFarMembers() {
//todo alle members die ver weg zijn worden geremoved
}

void Flock::update(float time) {
    //todo een manier vinden om alleen objecten mee te sturen die in de buurt zijn
    for (auto const &member: this->members) {
        member->updatePositions(members, time);
    }
}

void Flock::draw() {
    for (auto const &member: this->members) {
        member->draw();
    }
}
