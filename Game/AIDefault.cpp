
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


	//int count = 0;
	//Vector2f v(0.0f, 0.0f);

	//for (auto& a : *_konijnArray)
	//{
	//	if (a.get() == this)
	//		continue;

	//	float dis_x = ((a->Position->x + 5 / 2.0f) - (Position->x + 5 / 2.0f));
	//	float dis_y = ((a->Position->y + 5 / 2.0f) - (Position->y + 5 / 2.0f));
	//	float distance = abs(sqrtf(dis_x * dis_x + dis_y * dis_y));

	//	if (distance > 0 && distance <= RADIUS)
	//	{
	//		v.Add(*a->Velocity);
	//		count++;
	//	}
	//}

	//if (count > 0)
	//	v.Divide((float)count);

	//v.Limit(MAX_FORCE);

	//return v;

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

	//Vector2f sum(0.0f, 0.0f);
	//int count = 0;

	//for (auto& a : *_konijnArray)
	//{
	//	if (a.get() == this)
	//		continue;

	//	float dis_x = ((a->Position->x + 5 / 2.0f) - (Position->x + 5 / 2.0f));
	//	float dis_y = ((a->Position->y + 5 / 2.0f) - (Position->y + 5 / 2.0f));
	//	float distance = abs(sqrtf(dis_x * dis_x + dis_y * dis_y));

	//	if (distance > 0 && distance <= NEIGHBOUR_RADIUS)
	//	{
	//		sum.Add(*a->Position);
	//		count++;
	//	}
	//}

	//if (count > 0)
	//{
	//	Vector2f steer(0.0f, 0.0f);
	//	sum.Divide((float)count);

	//	// A vector pointing from the location to the target
	//	Vector2f desired = (sum - *Position);

	//	// Distance from the target is the magnitude of the vector
	//	float dis = desired.Magnitude();

	//	// If the distance is greater than 0, calc steering
	//	// (otherwise return zero vector)
	//	if (dis > 0)
	//	{
	//		desired.Normalize();

	//		// Two options for desired vector magnitude
	//		// (1 -- based on distance, 2 -- maxspeed)
	//		if (dis < NEIGHBOUR_RADIUS * 0.5f)
	//			desired.Multiply(MAX_SPEED * (dis / NEIGHBOUR_RADIUS)); // This damping is arbitrary
	//		else
	//			desired.Multiply(MAX_SPEED);

	//	}
	//	return desired.Limit(MAX_FORCE);
	//}
	//return sum; // No neighbours, no cohesion


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

	for (const auto& other : *PhysicsManager::Instance().GetCollidables()) {
		const auto& oX = other.GetMidX();
		const auto& oY = other.GetMidY();
		const auto& oWeight = other.GetWidth() * other.GetHeight() * COLLIDABLEWEIGHTMULTIPLIER;
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

	//Vector2f v(0.0f, 0.0f);
	//Vector2f temp(0.0f, 0.0f);
	//int count = 0;

	//// Surrounding bees
	//for (auto& a : *_konijnArray)
	//{
	//	if (a.get() == this)
	//		continue;

	//	float dis_x = ((a->Position->x + 5 / 2.0f) - (Position->x + 5 / 2.0f));
	//	float dis_y = ((a->Position->y + 5 / 2.0f) - (Position->y + 5 / 2.0f));
	//	float distance = abs(sqrtf(dis_x * dis_x + dis_y * dis_y));

	//	if (distance > 0 && distance <= SEPERATION_RADIUS)
	//	{
	//		// Normalized, weighted by distance vector pointing away from the neighbour
	//		temp.Set(*Position).Substract(*a->Position).Normalize();
	//		temp.Multiply(1.2f);
	//		temp.Divide(distance).Limit(MAX_FORCE);
	//		v.Add(temp);
	//		count++;
	//	}
	//}

	//if (count > 0)
	//	v.Divide((float)count);

	//return v;
}

void AIDefault::CohesePlayer()
{
	//Vector2f v(0.0f, 0.0f);
	//Vector2f temp(0.0f, 0.0f);
	//int count = 0;

	//// Beekeeper
	//float dis_x = (_schaap->GetTruePositionX() - (Position->x + width / 2.0f));
	//float dis_y = (_schaap->GetTruePositionY() - (Position->y + height / 2.0f));
	//float distance = abs(sqrtf(dis_x * dis_x + dis_y * dis_y));

	//if (distance > 0 && distance <= 50)
	//{
	//	temp.Set(*Position).Substract(*_schaap->GetPositionX(), *_schaap->GetPositionY()).Normalize();
	//	temp.Divide(-distance).Limit(MAX_FORCE);
	//	v.Add(temp);
	//	count++;
	//}

	//if (count > 0)
	//	v.Divide((float)count);

	//return v;
}

void AIDefault::GoTarget()
{
	_owner->SetDestinationPoint(_target->GetCoordinates());
}

AIDefault::~AIDefault() = default;