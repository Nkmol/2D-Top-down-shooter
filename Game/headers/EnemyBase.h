//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_ENEMYBASE_H
#define SHOOTER_ENEMYBASE_H


#include <Point.h>
#include <vector>
#include "memory"
#include "Player.h"
#include "MoveableObject.h"
#include "Helper.h"

class EnemyBase : public MoveableObject {

protected:
    using EnemiesType = vector<shared_ptr<EnemyBase>>;
    int lifepoints, reward, weightMultiplier = 100;
    Point destinationPoint;

    // Todo Smart pointer for non-owning pointer? (actually a nullable-reference) -> probably weak_ptr?
    const Player *_target;
    const EnemyBase *_leader;

    bool isLeader;

    const int getLifepoints() const;

    const int changeLifepoints(const int lp);

    const int getReward() const;


public:
    EnemyBase(const std::string &filePath, Point coordinates, float speed, bool isLeader, int damage, int lifepoints,
              int reward);

    void UpdatePositions(float time);

    //algorithms
    void Align();

    void Cohese(GameObject &other);

    void Seperate(GameObject &other);

    void ApplyForce(float forcePower, int forceDirection);

    virtual void GoTarget();

    //getters
    const Player &getTarget() const;

    //setters
    void setTarget(const Player &target);

    void setLeader(const EnemyBase &leader);

    void update(float time);

    void draw();

    void onCollision(GameObject object) override;

private:
    Point massCenter = Point(0, 0);
    int massSize = 0;
};


#endif //SHOOTER_ENEMYBASE_H
