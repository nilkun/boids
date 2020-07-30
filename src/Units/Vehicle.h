#pragma once
#include <vector>
#include "../Engine/fVector.h"
#include "./MovingEntity.h"

// class Flock;
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
		void pre();
		void update(float elapsed_time);
};
