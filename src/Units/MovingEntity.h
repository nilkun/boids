#pragma once
#include <SDL2/SDL.h>
#include "../Engine/fVector.h"
#include <vector>

class Vehicle;
class Flock 
{
	public:
		int SCREENWIDTH;
		int SCREENHEIGHT;
		std::vector<Vehicle*> boids;
		Flock(int w, int h); 
		void update(float delta);
		void render(SDL_Renderer *renderer);
};
class MovingEntity {
	protected:
	public:
		fVector velocity;
		fVector heading;
		fVector side;

		fVector position;
		fVector extraPos;
		bool isNearBottom;

		int SCREENWIDTH;
		int SCREENHEIGHT;

		std::vector<Vehicle*> boids;
		float mass = .5;
		float maxSpeed = 19;
		float maxForce = 39;
		float maxTurnRate = 3;
		float rad = 100;

		fVector steeringForce_;
	public:
		MovingEntity();
		void render(SDL_Renderer *renderer);
};
