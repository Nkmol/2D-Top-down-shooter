#include "AIDefault.h"
#include "EnemyBase.h"

void AIDefault::Update(float time)
{
	Align();
	Cohese();
	Seperate();
	CohesePlayer();
	
	auto& coordinates = _owner->GetCoordinates();
	auto& destinationPoint = _owner->GetDestinationPoint();

	const auto rad = atan2(coordinates.y - destinationPoint.y, coordinates.x - destinationPoint.x);
	const auto dir = Helper::RadiansToDegrees(rad);
	const auto correctedAngleRadians = Helper::DegreesToRadians(dir - 90);
	_owner->SetAngle(dir);

	_owner->SetDestination(Point(sin(correctedAngleRadians), -cos(correctedAngleRadians)));
}

void AIDefault::Align()
{
	_owner->SetDestinationPoint(_owner->_player->GetCoordinates());
}

void AIDefault::Cohese()
{
	Point massCenter(0, 0);
	for (const auto& other : *_owner->npcs) {
		
			if (other.get() != _owner) {
				const auto& oCoordinates = other->GetCoordinates();
				massCenter += oCoordinates;
			}
		
	}

	const auto othersSize = _owner->npcs->size() - 1;
	massCenter = massCenter / othersSize;

	auto& coordinates = _owner->GetCoordinates();
	const auto forceDirection = Helper::CalculateAngle(coordinates.x, coordinates.y, massCenter.x, massCenter.y);

	_owner->ApplyForce(0.1, forceDirection);
}

void AIDefault::Seperate()
{
	auto& coordinates = _owner->GetCoordinates();

	for (const auto& other : *_owner->npcs) {
			if (other.get() != _owner) {
				const auto& oWeight = other->GetWidth() * other->GetHeight() * _weightMultiplier;
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


	std::vector<GameObject*> temp = {};
	MapManager::Instance().getNearbyCollidables(coordinates, &temp);
	for (const auto& other : temp) {
		const auto& oX = other->GetMidX();
		const auto& oY = other->GetMidY();
		const auto& oWeight = other->GetWidth() * other->GetHeight() * COLLIDABLEWEIGHTMULTIPLIER;

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

void AIDefault::CohesePlayer()
{
}

void AIDefault::GoTarget()
{
	_owner->SetDestinationPoint(_target->GetCoordinates());
}

AIDefault::~AIDefault() = default;