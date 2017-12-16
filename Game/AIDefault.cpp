
#include "AIDefault.h"
#include "EnemyBase.h"

void AIDefault::Update(EnemiesType& others, int time)
{
	_owner->Acceleration->Empty();

	Align(others);
	Cohese(others);
	Seperate(others);

	*_owner->Velocity += *_owner->Acceleration;

	auto coords = _owner->GetCoordinates();
	_owner->SetDestination((coords + *_owner->Velocity) * _owner->speed);
	//_owner->_coordinates += *_owner->Velocity;
		//GoTarget();
	

	auto& coordinates = _owner->GetCoordinates();
	auto& destinationPoint = _owner->GetDestinationPoint();

	const auto rad = atan2(coordinates.y - destinationPoint.y, coordinates.x - destinationPoint.x);
	const auto dir = Helper::radiansToDegrees(rad);
	//const auto correctedAngleRadians = Helper::degreesToRadians(dir - 90);
	_owner->SetAngle(dir);

	//_owner->SetDestination(Point(sin(correctedAngleRadians), -cos(correctedAngleRadians)));
}

void AIDefault::Align(EnemiesType& others)
{
	int count = 0;
	Point p(0.0f, 0.0f);

	for (auto& other : others)
	{
		if (auto a = other.lock()) {

			float dis_x = ((a->getMidX() / 2.0f) - (_owner->getMidX() / 2.0f));
			float dis_y = ((a->getMidY() / 2.0f) - (_owner->getMidY() / 2.0f));
			float distance = abs(sqrtf(dis_x * dis_x + dis_y * dis_y));

			if (distance > 0 && distance <= 60.0f)
			{
				p += (*_owner->Velocity.get());
				count++;
			}
		}
	}

	if (count > 0)
		p/((float)count);

	*_owner->Acceleration.get()+=p;
}

void AIDefault::Cohese(EnemiesType& others)
{
	Point sum(0.0f, 0.0f);
	int count = 0;

	for (auto& other : others)
	{
		if (auto a = other.lock())
		{

			float dis_x = ((a->getMidX() / 2.0f) - (_owner->getMidX() / 2.0f));
			float dis_y = ((a->getMidY() / 2.0f) - (_owner->getMidY() / 2.0f));
			float distance = abs(sqrtf(dis_x * dis_x + dis_y * dis_y));

			if (distance > 0 && distance <= 60.0f)
			{
				sum+=a->GetCoordinates();
				count++;
			}

		}
	}

	if (count > 0)
	{
		Point steer(0.0f, 0.0f);
		sum/(float)count;

		// A vector pointing from the location to the target
		Point desired = (sum + (_owner->GetCoordinates()*-1));

		// Distance from the target is the magnitude of the vector
		float dis = sqrtf(desired.x * desired.x + desired.y * desired.y);

		// If the distance is greater than 0, calc steering
		// (otherwise return zero vector)
		if (dis > 0)
		{
			desired.x /= dis;
			desired.y /= dis;

			// Two options for desired vector magnitude
			// (1 -- based on distance, 2 -- maxspeed)
			if (dis < 60.0f * 0.5f)
				desired*(_owner->speed * (dis / 60.0f)); // This damping is arbitrary

		}
		*_owner->Acceleration.get() += desired;
	}
}

void AIDefault::Seperate(EnemiesType& others)
{
	auto& coordinates = _owner->GetCoordinates();

	for (const auto& other : others) {
		if (auto shOther = other.lock()) {
			if (shOther.get() != _owner) {
				const auto& oWeight = shOther->getWidth() * shOther->getHeight() * _weightMultiplier;
				const auto& oCoordinates = shOther->GetCoordinates();
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