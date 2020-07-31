#include "./Vehicle.h"
#include "./MovingEntity.h"

std::vector<Vehicle*> Vehicle::getNearby() {
	std::vector<Vehicle*> nearby;
	for(int i = 0; i < friends -> boids.size(); i++) {
		Vehicle* current = friends -> boids[i];
		if(current == this) {
			continue;
		}
		fVector dist = current -> position - position;
		float hypo = dist.x * dist.x + dist.y * dist.y;
		if(hypo < rad * rad) 
		{
			nearby.push_back(current);
		}
		else if(isNearBottom) {
			if(!current -> isNearBottom) continue;
			fVector test1 = { 
				(abs(position.x - current -> position.x) > rad) ? current -> extraPos.x : current -> position.x,
				(abs(position.y - current -> position.y) > rad) ? current -> extraPos.y : current -> position.y
			};
	
			fVector dist = position - test1;
			float hypo = dist.x * dist.x + dist.y * dist.y;
			if(hypo < rad * rad) 
			{
				nearby.push_back(current);
			}
		}
	}
	return nearby;
}
fVector Vehicle::steering() {
	fVector total = { 0, 0 };
	float separationWeight = 8000;
	float alignmentWeight = 100;
	float cohesionWeight = 50;

	std::vector<Vehicle*> close = getNearby();
	if(close.size() < 2 ) return total;
	// flock
	// separation separation all
	fVector separation{0, 0};
	fVector alignment{0, 0};
	fVector cohesion{0, 0};
	for(int i = 0; i < close.size(); i++) {
		Vehicle *current = close[i];
		if(current == this) continue;

		fVector test1 = { 
			(abs(position.x - current -> position.x) > rad) ? current -> extraPos.x : current -> position.x,
			(abs(position.y - current -> position.y) > rad) ? current -> extraPos.y : current -> position.y
		};
		
		fVector distance = position - test1;

		// separation += distance.getNormal() / distance.length();
		separation += distance.getNormal() / distance.getLength();
		alignment += current -> heading;
		cohesion += test1;
	}
	// std::cout << separation.x << " x " << alignment.x << " x " << cohesion.x << std::endl;
	// cohesion = (cohesion / close.size() - this -> position ).getNormal() ;
	cohesion = (cohesion / (close.size()-1)) - position;
    // separation = (separation /close.size()) * -1;	
	// separation = separation / separation.length()
	separation = separation;
	alignment = (alignment / (close.size()-1));// - this -> heading;
	// alignment = alignment.setMag(1);
	total = separation * separationWeight + alignment * alignmentWeight + cohesion * cohesionWeight;
	// alignmentment go for same heading
	// cohesion average

	return total;
}
Vehicle::Vehicle(Flock *flock) {
	friends = flock;
	// super();
}
void Vehicle::pre(){
	steeringForce_ = steering();
}
void Vehicle::update(float elapsed_time) {
	// fVector steeringForce_ = steering();
	// { 1, 0 };
	// = steering -> calculate();
	fVector acceleration_ = steeringForce_ / mass;
	velocity += acceleration_ * elapsed_time;
	velocity.truncate(maxSpeed);
	position += velocity * elapsed_time;
//
	int SCREENWIDTH = 1360;
	int SCREENHEIGHT = 768;
	if(position.x > 1360) position.x -= 1360;
	else if (position.x < 0) position.x += 1360;
    if(position.y > 768) position.y -= 768;
	else if (position.y <0) position.y += 768;	

	if(velocity.getLengthSq() > 0.00000001)
	{
		heading = velocity.getNormal();
		side = heading.getPerpendicular();
	}
	
	// Find close in torus
	isNearBottom = false;
	if(position.x < rad) {
		extraPos.x = 1360 + position.x;
		extraPos.y = position.y;
		isNearBottom = true;
	}	
	else if(position.x > 1360 - rad) {
		extraPos.x = position.x - 1360;
		extraPos.y = position.y;
		isNearBottom = true;
	}	
	if(position.y > 768 - rad) 
	{ 
		if(!isNearBottom) extraPos.x = position.x;
		extraPos.y = position.y - 768;
		isNearBottom = true;
	}
	if(position.y < rad) 
	{ 
		if(!isNearBottom) extraPos.x = position.x;
		extraPos.y = 768 + position.y;
		isNearBottom = true;
	}
}
