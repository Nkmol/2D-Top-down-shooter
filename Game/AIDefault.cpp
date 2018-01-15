#include "AIDefault.h"
#include "EnemyBase.h"

void AIDefault::Update(float time)
{
	const auto align = Align();
	ApplyForce(align);

	const auto cohese = Cohese();
	ApplyForce(cohese);

	const auto separate = Seperate();
	ApplyForce(separate);

	auto to = seek(*_target);
	to *= 1;
	ApplyForce(to);

	_velocity += acceleration_;
	_velocity.limit(_maxSpeed);
	_owner->SetSpeed(_velocity.x);

	auto& coordinates = _owner->GetCoordinates();
	//auto& destinationPoint = _owner->GetDestinationPoint();

	const auto rad = atan2(to.y, to.x);
	auto deg = Helper::RadiansToDegrees(rad);
	deg -= 180; // TODO is quickfix
	_owner->SetAngle(deg);

	//std::cout << "Object wants to move to " << Point(float(x), float(y)) << " with a steering translation of " << acceleration_ << " relative on current coordinates " << _owner->GetCoordinates() << std::endl;
	//auto& coordinates = _owner->GetCoordinates();
	_owner->SetCoordinates(_owner->GetCoordinates() + _velocity);
	//auto& t = _owner->GetCoordinates();
	//owner->SetDestination(Point(sin(correctedAngleRadians), -cos(correctedAngleRadians)));
	
	// reset
	acceleration_ = {};
}

void AIDefault::ApplyForce(const Point& force) 
{
	acceleration_ += force;
}

//void AIDefault::Align()
//{
//	/*_owner->SetDestinationPoint(_owner->_player->GetCoordinates());*/
//
//}

// Alignment
// For every nearby boid in the system, calculate the average velocity
Point AIDefault::Align()
{
	const auto neighbordist = 50.0f;

	Point sum;
	auto count = 0;

	for (auto&& other : *_owner->npcs)
	{
		const auto dist = _owner->GetCoordinates().dist(other->GetCoordinates());
		if (dist > 0 && dist < neighbordist)
		{
			sum += other->GetCoordinates();
			sum += other->GetSpeed();

			count++;
		}
	}

	if (count > 0)
	{
		sum /= count;

		sum.normalize();
		sum = sum * _maxSpeed;

		sum -= _owner->GetSpeed();

		sum.limit(_maxForce);
	}

	return sum;
}

Point AIDefault::Cohese()
{
	/*Point massCenter(0, 0);
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

	_owner->ApplyForce(0.1, forceDirection);*/

	const auto neighbordist = 50.0f;

	Point mass_center;
	auto count = 0;

	for (auto&& other : *_owner->npcs) {
      const auto dist =	_owner->GetCoordinates().dist(other->GetCoordinates());
      if (dist > 0 && dist< neighbordist) {
        mass_center += other->GetCoordinates();
        count++;
      }
    }

	if (count > 0) {
		mass_center /= count;

	    mass_center = seek(mass_center);
	} 

	return mass_center;
}

// A method that calculates and applies a steering force towards a target
Point AIDefault::seek(const Point& target) const
{
	// A vector pointing from the location to the target
	auto desired = target - _owner->GetCoordinates();

	// Normalize desired and scale to maxium speed
	desired.normalize();
	desired *= _maxSpeed;

	// Steering = Desired minus Velocity
	auto steer = desired - _owner->GetSpeed();
	steer.limit(_maxForce);

	return steer;
}

// Separation
// Method checks for nearby boids and steers away
Point AIDefault::Seperate()
{
	Point sum;
	const auto desired_seperation = _owner->GetSize().length() * 2;
	auto count = 0;

	// For every boid in the system, check if it's too close
	for (auto && other : *_owner->npcs)
	{
		const auto dist = _owner->GetCoordinates().dist(other->GetCoordinates());
		if(dist > 0 && dist < desired_seperation)
		{
			// Calculate vector pointing away from neighbor
			auto heading_vector = _owner->GetCoordinates() - other->GetCoordinates();

			heading_vector.normalize();
			heading_vector /= dist;

			// The closer we are, the more intense the force vector will be
			sum += heading_vector;

			count++;
		}
	}

	std::vector<GameObject*> temp = {};
	MapManager::Instance().getNearbyCollidables(_owner->GetCoordinates(), &temp);
	for (const auto& other : temp) {
		const auto dist = _owner->GetCoordinates().dist(other->GetCoordinates());
		if(dist > 0 && dist < desired_seperation)
		{
			// Calculate vector pointing away from neighbor
			auto heading_vector = _owner->GetCoordinates() - other->GetCoordinates();

			heading_vector.normalize();
			heading_vector /= dist;

			// The closer we are, the more intense the force vector will be
			sum += heading_vector;

			count++;
		}
	}

	// Average -- divide by how many
	if(count > 0)
	{
		sum /= count;
		sum.normalize();
		sum = sum * _maxSpeed;
		sum -= _owner->GetSpeed();

		sum.limit(_maxForce);
	}

	return sum;
}


//
//void AIDefault::Seperate()
//{
//	auto& coordinates = _owner->GetCoordinates();
//
//	for (const auto& other : *_owner->npcs) {
//			if (other.get() != _owner) {
//				const auto& oWeight = other->GetWidth() * other->GetHeight() * _weightMultiplier;
//				const auto& oCoordinates = other->GetCoordinates();
//				const Point squared((oCoordinates.x - coordinates.x) * (oCoordinates.x - coordinates.x),
//					(oCoordinates.y - coordinates.y) * (oCoordinates.y - coordinates.y));
//				const auto squareDist = squared.x + squared.y;
//				if (squareDist < oWeight) {
//					const auto headingVector = Point(coordinates.x - oCoordinates.x, coordinates.y - oCoordinates.y);
//					const auto scale = sqrt(squareDist) / sqrt(oWeight);
//					const auto scaledVector = headingVector / sqrt(squareDist) / scale;
//
//					_owner->SetDestinationPoint(_owner->GetDestinationPoint() + scaledVector);
//				}
//			}
//	}
//
//
//	std::vector<GameObject*> temp = {};
//	MapManager::Instance().getNearbyCollidables(coordinates, &temp);
//	for (const auto& other : temp) {
//		const auto& oX = other->GetMidX();
//		const auto& oY = other->GetMidY();
//		const auto& oWeight = other->GetWidth() * other->GetHeight() * COLLIDABLEWEIGHTMULTIPLIER;
//
//		const auto& m = coordinates;
//		const Point squared((oX - m.x) * (oX - m.x), (oY - m.y) * (oY - m.y));
//		const auto squareDist = squared.x + squared.y;
//		if (squareDist < oWeight) {
//			const Point headingVector(m.x - oX, m.y - oY);
//			const auto scale = sqrt(squareDist) / sqrt(oWeight);
//			const auto scaledVector = headingVector / sqrt(squareDist) / scale;
//			
//			_owner->SetDestinationPoint(_owner->GetDestinationPoint() + scaledVector);
//		}
//	}
//}

//void AIDefault::CohesePlayer()
//{
//}

void AIDefault::GoTarget()
{
	_owner->SetDestinationPoint(*_target);
}

AIDefault::~AIDefault() = default;