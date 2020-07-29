#include "./MovingEntity.h"
#include "../Engine/nilkun.h"
int SCREENWIDTH = 960;
int SCREENHEIGHT = 540;
float rad = 100;
void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		SDL_RenderDrawPoint(renderer,centreX+x,centreY-y);
		SDL_RenderDrawPoint(renderer,centreX+x,centreY+y);
		SDL_RenderDrawPoint(renderer,centreX-x,centreY-y);
		SDL_RenderDrawPoint(renderer,centreX-x,centreY+y);
		SDL_RenderDrawPoint(renderer,centreX+y,centreY-x);
		SDL_RenderDrawPoint(renderer,centreX+y,centreY+x);
		SDL_RenderDrawPoint(renderer,centreX-y,centreY-x);
		SDL_RenderDrawPoint(renderer,centreX-y,centreY+x);
		if(error<=0)
		{
			++y;
			error+=ty;
			ty+=2;
		}

		if(error>0)
		{
			--x;
			tx+=2;
			error+=(tx-diameter);
		}
	}
}

fVector fVector::getNormalized() {
	float h = getHypoteneuse();
	fVector normalized = { x / h, y / h };
	return normalized;
}
float fVector::getHypoteneuse() {
	return sqrt(x*x+y*y);
}
float fVector::length() {
	return getHypoteneuse();
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
void fVector::setMag(float mag) {
	float scalar = getHypoteneuse();
	x = x / scalar * mag;
	y = y / scalar * mag;
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
	for(int i = 0; i < 300; i++) boids.push_back(new Vehicle(this));
}

void Flock::update(float delta) {
	for(int i = 0; i < boids.size(); i++) boids[i] -> pre();//0.016);	
	for(int i = 0; i < boids.size(); i++) boids[i] -> update(0.016);	
}
void Flock::render(SDL_Renderer *renderer) {
		for(int i = 0; i < boids.size(); i++) boids[i] -> render(renderer);	
		DrawCircle(renderer, boids[0] -> position.x, boids[0] -> position.y, rad);
}
MovingEntity::MovingEntity() {
	float direction = (nilkun::random(1, 360)/360.0f)*6.2308f;
	heading = { cos(direction), sin(direction) };
	side = { sin(direction), -cos(direction) };
	position = { nilkun::random(0, 959), nilkun::random(0,539)};
	maxSpeed = 60; //nilkun::random(60, 100);
	velocity = { cos(direction)*maxSpeed, sin(direction)*maxSpeed };
	mass = 1;
	isNearBottom = false;

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
		if(hypo < rad * rad) 
		{
			nearby.push_back(current);
		}
		else if(isNearBottom) {
			fVector dist = current -> position - extraPos;
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
	float alignmentWeight = 0;//100;
	float cohesionWeight = 0;//50;

	std::vector<Vehicle*> close = getNearby();
	if(close.size() < 2 ) return total;
	// flock
	// separation separation all
	fVector separation{0, 0};
	fVector alignment{0, 0};
	fVector cohesion{0, 0};
	fVector *own;
	for(int i = 0; i < close.size(); i++) {
		
		Vehicle *current = close[i];
		own = 
			current -> isNearBottom 
			? &current -> extraPos
			: &current -> position;

		if(current == this) continue;
		fVector distance = position - *own;

		// separation += distance.getNormalized() / distance.length();
		separation += distance.getNormalized() / distance.length();
		alignment += current -> heading;
		cohesion += *own;
	}
	// std::cout << separation.x << " x " << alignment.x << " x " << cohesion.x << std::endl;
	// cohesion = (cohesion / close.size() - this -> position ).getNormalized() ;
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
	isNearBottom = false;
	if(position.x < 100) {
		extraPos.x = 960 + position.x;
		extraPos.y = position.y;
	}	
	if(position.x < 100 || position.x > 860) {
		extraPos.x = position.x - 960;
		if 
		isNearBottom = true;
		if(position.y > 440 || position.y < 100) 
		{ 
			extraPos.y = 540 - position.y;
		}
		else extraPos.y = position.y;
	}	
	else if(position.y > 440 || position.y < 100) 
	{ 
		extraPos.x = position.x;
		extraPos.y = 540 - position.y;
		isNearBottom = true;

	}
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
