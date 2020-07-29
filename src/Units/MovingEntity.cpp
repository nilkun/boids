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
// SDL_Point* getNewPoints(SDL_Point[4] points, int x, int y) {	
	// SDL_Point*  newPoints = new SDL_Point[4];
		// *newPoints[0] =	{ points[0].x + x, points[0].y + y };
		// *newPoints[1] = { points[1].x + x, points[1].y + y };
		// *newPoints[2] =	{ points[2].x + x, points[2].y + y };
		// *newPoints[3] =	{ points[3].x + x, points[3].y + y };
	// }
	// return newPoints;
// };
void setNewPoints(SDL_Point newPoints[4], SDL_Point points[4], int x, int y) {
		newPoints[0].x = points[0].x + x;
		newPoints[0].y = points[0].y + y;
		newPoints[1].x = points[1].x + x;
		newPoints[1].y = points[1].y + y;
		newPoints[2].x = points[2].x + x;
		newPoints[2].y = points[2].y + y; 
		newPoints[3].x = points[3].x + x;
		newPoints[3].y = points[3].y + y;
};
void MovingEntity::render(SDL_Renderer *renderer) {
	int length = 15;
	int radius = 5;
	SDL_Point points[] = {
		{ static_cast<int>(position.x + heading.x * length), static_cast<int>(position.y + heading.y * length) },
		{ static_cast<int>(position.x + side.x * radius), static_cast<int>(position.y + side.y * radius) },
		{ static_cast<int>(position.x - side.x * radius), static_cast<int>(position.y - side.y * radius )},
		{ static_cast<int>(position.x + heading.x * length), static_cast<int>(position.y + heading.y * length )}
	};
	int count = 4; 
	SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255); // SET SCREEN TO BLACK
	SDL_RenderDrawLines(renderer, points, count);
	
SDL_Point extra[4];
SDL_Point extra2[4];
SDL_Point extra3[4];

	if(position.x < length) {
		setNewPoints(extra, points, 960, 0);
		SDL_RenderDrawLines(renderer, extra, count);
		if(position.y < length) {
			setNewPoints(extra2, extra, 0, 540);
			setNewPoints(extra3, points, 0, 540);
			SDL_RenderDrawLines(renderer, extra2, count);
			SDL_RenderDrawLines(renderer, extra3, count);
		}
		else if(position.y + length > 540) {
			setNewPoints(extra2, extra, 0, -540);
			setNewPoints(extra3, points, 0, -540);
			SDL_RenderDrawLines(renderer, extra2, count);
			SDL_RenderDrawLines(renderer, extra3, count);
		}
	}
	else if(position.x + length > 960) {
		setNewPoints(extra, points, -960, 0);
		SDL_RenderDrawLines(renderer, extra, count);
		if(position.y < length) {
			setNewPoints(extra2, extra, 0, 540);
			setNewPoints(extra3, points, 0, 540);
			SDL_RenderDrawLines(renderer, extra2, count);
			SDL_RenderDrawLines(renderer, extra3, count);
		}
		else if(position.y + length > 540) {
			setNewPoints(extra2, extra, 0, -540);
			setNewPoints(extra3, points, 0, -540);
			SDL_RenderDrawLines(renderer, extra2, count);
			SDL_RenderDrawLines(renderer, extra3, count);
		}
	}
	else if(position.y < length) {
			setNewPoints(extra, points, 0, 540);
			SDL_RenderDrawLines(renderer, extra, count);
		}
		else if(position.y + length > 540) {
			setNewPoints(extra, points, 0, -540);
			SDL_RenderDrawLines(renderer, extra, count);
		}
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
	float alignmentWeight = 100;
	float cohesionWeight = 50;

	std::vector<Vehicle*> close = getNearby();
	if(close.size() < 2 ) return total;
	// flock
	// separation separation all
	fVector separation{0, 0};
	fVector alignment{0, 0};
	fVector cohesion{0, 0};
	fVector *pos;
	for(int i = 0; i < close.size(); i++) {
		
		Vehicle *current = close[i];
		pos = 
			current -> isNearBottom 
			? &close[i] -> extraPos
			: &close[i] -> position;
		fVector test1 = { 
			(abs(position.x - current -> position.x) > 100) ? current -> extraPos.x : current -> position.x,
			(abs(position.y - current -> position.y) > 100) ? current -> extraPos.y : current -> position.y
		};
		
		if(current == this) continue;
		fVector distance = position - test1;

		// separation += distance.getNormalized() / distance.length();
		separation += distance.getNormalized() / distance.length();
		alignment += current -> heading;
		cohesion += test1;
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

	if(position.x > 960) position.x -= 960;
	else if (position.x < 0) position.x += 960;
    if(position.y > 540) position.y -= 540;
	else if (position.y <0) position.y += 540;	

	if(velocity.lengthSq() > 0.00000001)
	{
		heading = velocity.getNormalized();
		side = heading.getPerp();
	}
	
	// Find close in torus
	isNearBottom = false;
	if(position.x < 100) {
		extraPos.x = 960 + position.x;
		extraPos.y = position.y;
		isNearBottom = true;
	}	
	else if(position.x > 860) {
		extraPos.x = position.x - 960;
		isNearBottom = true;
		extraPos.y = position.y;
	}	
	if(position.y > 440) 
	{ 
		if(!isNearBottom) extraPos.x = position.x;
		isNearBottom = true;
		extraPos.y = position.y - 540;
	}
	if(position.y < 100) 
	{ 
		if(!isNearBottom) extraPos.x = position.x;
		extraPos.y = 540 + position.y;
		isNearBottom = true;
	}
}
