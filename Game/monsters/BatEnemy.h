//
// Created by Ahmad Rahimi on 11/29/17.
//

#ifndef SHOOTER_BATENEMY_H
#define SHOOTER_BATENEMY_H


#include <EnemyBase.h>

class BatEnemy : public EnemyBase
{
public:
	BatEnemy(const Point& coordinates, bool isLeader);
	void update(float time) override;
	void GoTarget() override;
private:
	int _currentUpdateCounter = 0, _maxUpdateCounter = 50;
	bool _attackTarget = true;
};


#endif //SHOOTER_BATENEMY_H
