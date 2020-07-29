#include "./MovingEntity.h"
#include "../Engine/nilkun.h"

fVector fVector::getNormalized() {
	float h = getHypoteneuse();
	fVector normalized = { x / h, y / h };
	return normalized;
}
float fVector::getHypoteneuse() {
	return sqrt(x*x+y*y);
}
fVector fVector::getPerp() {
	return fVector { y, -x };
}
void fVector::truncate(float maxValue) {
	if(maxValue * maxValue < x * x + y * y) {
		float h = getHypoteneuse();
		x /= h;
		y /= h;
		x *= maxValue;
		y *= maxValue;
	};
}
float fVector::lengthSq() { return x * x + y * y; }
fVector fVector::operator/(float &rhs)
{
	if(rhs==0) return fVector{0, 0};
	fVector divided = {
		x / rhs,
		y / rhs
	};
	return divided;
}
fVector fVector::operator/(const float &rhs) 
{
	return fVector { x / rhs, y / rhs };
};
fVector fVector::operator*(const float &rhs) 
{
	return fVector { x * rhs, y * rhs };
};
fVector fVector::operator+(const fVector &rhs) 
{
	return fVector { x + rhs.x, y + rhs.y };
};
fVector fVector::operator-(const fVector &rhs) 
{
	return fVector { x - rhs.x, y - rhs.y };
};
fVector& fVector::operator=(const fVector &rhs) {
	this -> x = rhs.x;
	this -> y = rhs.y;
	return *this;
}
fVector& fVector::operator+=(const fVector &rhs) {
	this -> x += rhs.x;
	this -> y += rhs.y;
	return *this;
};
Flock::Flock() 
{
	for(int i = 0; i < 30; i++) boids.push_back(new Vehicle(this));
}

void Flock::update(float delta) {
	for(int i = 0; i < boids.size(); i++) boids[i] -> update(0.016);	
}
void Flock::render(SDL_Renderer *renderer) {
		for(int i = 0; i < boids.size(); i++) boids[i] -> render(renderer);	
}
MovingEntity::MovingEntity() {
	float direction = (nilkun::random(1, 360)/360.0f)*6.2308f;
	heading = { cos(direction), sin(direction) };
	side = { sin(direction), -cos(direction) };
	position = { nilkun::random(0, 959), nilkun::random(0,539)};
	maxSpeed = nilkun::random(35, 50);
	velocity = { cos(direction)*maxSpeed, sin(direction)*maxSpeed };
};

void MovingEntity::render(SDL_Renderer *renderer) {
	SDL_Point points[] = {
		{ static_cast<int>(position.x + heading.x * 15), static_cast<int>(position.y + heading.y * 15) },
		{ static_cast<int>(position.x + side.x * 5), static_cast<int>(position.y + side.y * 5) },
		{ static_cast<int>(position.x - side.x * 5), static_cast<int>(position.y - side.y * 5 )},
		{ static_cast<int>(position.x + heading.x * 15), static_cast<int>(position.y + heading.y * 15 )}
	};
	int count = 4; 
	SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255); // SET SCREEN TO BLACK
	SDL_RenderDrawLines(renderer, points, count);
};

std::vector<Vehicle*> Vehicle::getNearby() {
	std::vector<Vehicle*> nearby;
	for(int i = 0; i < friends -> boids.size(); i++) {
		Vehicle* current = friends -> boids[i];
		if(current == this) {
			continue;
		}
		fVector dist = current -> position - position;
		float hypo = dist.x * dist.x + dist.y * dist.y;
		if(hypo < 3500) nearby.push_back(current);
	}
	return nearby;
}
fVector Vehicle::steering() {
	fVector total = { 0, 0 };

	std::vector<Vehicle*> close = getNearby();
	if(close.size() < 1 ) return total;
	// flock
	// separation avoid all
	fVector avoid{0, 0};
	fVector align{0, 0};
	fVector cohesion{0, 0};
	for(int i = 0; i < close.size(); i++) {
		Vehicle *current = close[i];
		avoid += current -> position - this -> position;
		align += current -> heading;
		cohesion += current -> position;
	}
	// std::cout << avoid.x << " x " << align.x << " x " << cohesion.x << std::endl;
    avoid = (avoid * -1).getNormalized();	
	align = align.getNormalized();
	cohesion = (cohesion / close.size() - this -> position ).getNormalized() ;
	total = avoid + align + cohesion;
	// alignment go for same heading
	// cohesion average

	return total;
}
Vehicle::Vehicle(Flock *flock) {
	friends = flock;
	// super();
}
void Vehicle::update(float elapsed_time) {
	fVector steeringForce_ = steering();
	// { 1, 0 };
	// = steering -> calculate();
	fVector acceleration_ = steeringForce_ *100; /// mass;
	velocity += acceleration_ * elapsed_time;
	velocity.truncate(maxSpeed);
	position += velocity * elapsed_time;
//
	if(position.x > 960) position.x -= 960;
	else if (position.x < 0) position.x += 960;
    if(position.y > 540) position.y -= 540;
	else if (position.y <0) position.y += 540;	
	if(velocity.lengthSq() > 0.00000001)
	{
		heading = velocity.getNormalized();
		side = heading.getPerp();
	}
}
