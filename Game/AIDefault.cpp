
#include "AIDefault.h"
#include "typeinfo"

//void AIDefault::Update(EnemiesType& others, int time)
//{
//	if (!_isLeader) {
//		Align();
//		Cohese(others);
//		Seperate(others);
//	}
//	else {
//		GoTarget();
//	}
//
//	auto& coordinates = _owner->GetCoordinates();
//	auto& destinationPoint = _owner->GetDestinationPoint();
//
//	const auto rad = atan2(coordinates.y - destinationPoint.y, coordinates.x - destinationPoint.x);
//	const auto dir = Helper::radiansToDegrees(rad);
//	const auto correctedAngleRadians = Helper::degreesToRadians(dir - 90);
//	_owner->SetAngle(dir);
//
//	_owner->SetDestination(Point(sin(correctedAngleRadians), -cos(correctedAngleRadians)));
//}

void AIDefault::Update(int time) {
	auto& coordinates = _owner->GetCoordinates();
	auto& destinationPoint = _owner->GetDestinationPoint();

		massCenter = Point(0,0);
		massSize = 0;
		std::vector<reference_wrapper<GameObject>> neighbours = this->_owner->getNearbyObjects();//PhysicsManager::Instance().RetrieveNearbyGameObjects(*_owner);
		NonNeighbourRelatedBehaviour();
		for (auto& other: neighbours) {
			NeighbourRelatedBehaviour(&other.get());
		}
		const auto forceDirection = Helper::calculateAngle(coordinates.x, coordinates.y, massCenter.x, massCenter.y);
		_owner->ApplyForce(0.1, forceDirection);

	//calculate destinationpoint after all forces are applied
	const auto rad = (atan2(coordinates.y - destinationPoint.y, coordinates.x - destinationPoint.x));
	const auto dir = Helper::radiansToDegrees(rad);
	const auto correctedAngleRadians = Helper::degreesToRadians(dir - 90);
	_owner->SetAngle(dir);

	_owner->SetDestination(Point(sin(correctedAngleRadians), -cos(correctedAngleRadians)));
}

void AIDefault::Align()
{
	auto& dest = _leader->GetDestinationPoint();
	_owner->SetDestinationPoint(dest);
}

void AIDefault::Align(const GameObject *other) {
	if (other->GetId() != this->_owner->GetId()) {
		const auto *p = dynamic_cast<const EnemyBase*>(other);
		if(p) {
			const auto &oCoordinates = p->GetDestination();
			massCenter += oCoordinates;
		}
	}
}

void AIDefault::Cohese(const GameObject *other) {
	if (other->GetId() != this->_owner->GetId()) {
		const auto *p = dynamic_cast<const EnemyBase*>(other);
		if(p) {
			const auto &oCoordinates = other->GetCoordinates();
			massCenter += oCoordinates;
		}
	}
}

void AIDefault::Seperate(const GameObject *other) {
	auto& coordinates = _owner->GetCoordinates();
	if (other->GetId() != this->_owner->GetId()) {
		//teamid -100 are collidables
		const auto &oWeight = other->getWidth() * other->getHeight() * (other->GetTeamId() != -100 ? _weightMultiplier : COLLIDABLEWEIGHTMULTIPLIER);
		const auto &oCoordinates = other->GetCoordinates();
		const Point squared((oCoordinates.x - coordinates.x) * (oCoordinates.x - coordinates.x),
							(oCoordinates.y - coordinates.y) * (oCoordinates.y - coordinates.y));
		const auto squareDist = squared.x + squared.y;
		if (squareDist < oWeight) {
			const auto headingVector = Point(coordinates.x - oCoordinates.x, coordinates.y - oCoordinates.y);
			const auto scale = sqrt(squareDist) / sqrt(oWeight);
			const auto scaledVector = headingVector / sqrt(squareDist) / scale;
			_owner->SetDestinationPoint(_owner->GetDestinationPoint() + scaledVector);
		}
	}
}

void AIDefault::GoTarget()
{
	_owner->SetDestinationPoint(_target->GetCoordinates());
}

void AIDefault::NonNeighbourRelatedBehaviour() {
	GoTarget();
}

void AIDefault::NeighbourRelatedBehaviour(const GameObject *other) {
	Cohese(other);
	Align(other);
	//apply cohesion force
	massCenter = massCenter / massSize;
	Seperate(other);
}

AIDefault::~AIDefault() = default;