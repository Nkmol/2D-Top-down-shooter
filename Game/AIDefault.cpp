
#include "AIDefault.h"
#include "EnemyBase.h"

void AIDefault::Update(EnemiesType& others, int time)
{
	if (!_isLeader) {
		Align();
		Cohese(others);
		Seperate(others);
	}
	else {
		GoTarget();
	}

	auto& coordinates = _owner->GetCoordinates();
	auto& destinationPoint = _owner->GetDestinationPoint();

	const auto rad = atan2(coordinates.y - destinationPoint.y, coordinates.x - destinationPoint.x);
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

void AIDefault::Cohese(EnemiesType& others)
{
	Point massCenter(0, 0);
	for (const auto& other : others) {
		if (other.get() != _owner) {

			const auto& oCoordinates = other->GetCoordinates();
			massCenter += oCoordinates;
		}
	}

	const auto othersSize = others.size() - 1;
	massCenter = massCenter / othersSize;

	auto& coordinates = _owner->GetCoordinates();
	const auto forceDirection = Helper::calculateAngle(coordinates.x, coordinates.y, massCenter.x, massCenter.y);

	_owner->ApplyForce(0.1, forceDirection);
}

void AIDefault::Seperate(EnemiesType& others)
{
	auto& coordinates = _owner->GetCoordinates();

	for (const auto& other : others) {
		if (other.get() != _owner) {
			const auto& oWeight = other->getWidth() * other->getHeight() * _weightMultiplier;
			const auto& oCoordinates = other->GetCoordinates();
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

	for (const auto& other : *PhysicsManager::Instance().getCollidables()) {
		const auto& oX = other.getMidX();
		const auto& oY = other.getMidY();
		const auto& oWeight = other.getWidth() * other.getHeight() * COLLIDABLEWEIGHTMULTIPLIER;
		const auto& m = coordinates;
		const Point squared((oX - m.x) * (oX - m.x), (oY - m.y) * (oY - m.y));
		const auto squareDist = squared.x + squared.y;
		if (squareDist < oWeight) {
			const Point headingVector(m.x - oX, m.y - oY);
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