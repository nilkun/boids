#include "./MovingEntity.h"
#include "../Engine/nilkun.h"
#include "./Vehicle.h"

int SCREENWIDTH = 960;
int SCREENHEIGHT = 540;
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

Flock::Flock() 
{
	for(int i = 0; i < 500; i++) boids.push_back(new Vehicle(this));
}

void Flock::update(float delta) {
	for(int i = 0; i < boids.size(); i++) boids[i] -> pre();//0.016);	
	for(int i = 0; i < boids.size(); i++) boids[i] -> update(0.016);	
}
void Flock::render(SDL_Renderer *renderer) {
		for(int i = 0; i < boids.size(); i++) boids[i] -> render(renderer);	
		// DrawCircle(renderer, boids[0] -> position.x, boids[0] -> position.y, rad);
}
MovingEntity::MovingEntity() {
	float direction = (nilkun::random(1, 360)/360.0f)*6.2308f;
	heading = { cos(direction), sin(direction) };
	side = { sin(direction), -cos(direction) };
	position = { static_cast<float>(nilkun::random(0, 959)), static_cast<float>(nilkun::random(0,539))};
	maxSpeed = nilkun::random(260, 300);
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
	int length = 5;
	int radius = 2;
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
