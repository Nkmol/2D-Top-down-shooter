
#include "AIDefault.h"
#include "EnemyBase.h"

void AIDefault::Update(EnemiesType& others, int time)
{
	auto& coordinates = _owner->GetCoordinates();
	auto& destinationPoint = _owner->GetDestinationPoint();

	if (!_isLeader) {
		_massCenter = Point(0, 0);
		_massSize = 0;
		std::vector<GameObject> neighbours = PhysicsManager::Instance().RetrieveNearbyGameObjects(*_owner);
		Align();
		for (auto& other : neighbours) {
			Cohese(other);
			//apply cohesion force
			_massCenter = _massCenter / _massSize;
			Seperate(other);
		}
		const auto forceDirection = Helper::calculateAngle(coordinates.x, coordinates.y, _massCenter.x, _massCenter.y);
		_owner->ApplyForce(0.1, forceDirection);

	}
	else {
		GoTarget();
	}

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

void AIDefault::Cohese(GameObject& other)
{
	if (other.GetId() != _owner->GetId()) {
		if (other.GetTeamId() == _owner->GetTeamId()) {
			const auto &oCoordinates = other.GetCoordinates();
			_massCenter += oCoordinates;
		}
	}
}

void AIDefault::Seperate(GameObject &other) {
	auto& coordinates = _owner->GetCoordinates();

	if (other.GetId() != _owner->GetId()) {
		//teamid -100 are collidables
		const auto &oWeight = other.getWidth() * other.getHeight() * (other.GetTeamId() != -100 ? _weightMultiplier : COLLIDABLEWEIGHTMULTIPLIER);
		const auto &oCoordinates = other.GetCoordinates();
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

AIDefault::~AIDefault() = default;