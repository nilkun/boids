#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>

struct fVector {
	float x;
	float y;
	fVector getNormalized();
	float getHypoteneuse();
	fVector getPerp();
	void truncate(float maxValue);
	float lengthSq();
	fVector operator/(float &rhs);
	fVector operator/(const float &rhs); 
	fVector operator*(const float &rhs); 
	fVector operator+(const fVector &rhs); 
	fVector operator-(const fVector &rhs); 
	fVector& operator=(const fVector &rhs);
	fVector& operator+=(const fVector &rhs);
};
class Vehicle;
class Flock 
{
	public:
		std::vector<Vehicle*> boids;
		Flock(); 
		void update(float delta);
		void render(SDL_Renderer *renderer);
};
class MovingEntity {
	protected:
		fVector velocity;
		fVector heading;
		fVector side;

		fVector position;

		float mass = .5;
		float maxSpeed = 19;
		float maxForce = 39;
		float maxTurnRate = 3;
	public:
		MovingEntity();
		void render(SDL_Renderer *renderer);
};

class Vehicle : public MovingEntity
{
	private:
		// pointer to game world
		Flock *friends;
		// SteeringBehaviours* steering;
	public:
		std::vector<Vehicle*> getNearby();
		fVector steering();
		Vehicle(Flock *flock);
		void update(float elapsed_time);
};
