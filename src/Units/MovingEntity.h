#pragma once
#include <iostream>
#include <cmath>

struct fVector {
	float x;
	float y;
	fVector getNormalized() {
		float h = getHypoteneuse();

		fVector normalized = { x / h, y / h };
		return normalized;
	}
	float getHypoteneuse() {
		return sqrt(x*x+y*y);
	}
	fVector getPerp() {
		return fVector { y, -x };
	}
	void truncate(float maxValue) {
		if(maxValue * maxValue > x * x + y * y) {
			float h = getHypoteneuse();
			x /= h;
			y /= h;
			x *= maxValue;
			y *= maxValue;
		};
				   
	}

	float lengthSq() { return x * x + y * y; }
	fVector operator/(float &rhs)
	{
		if(rhs==0) return fVector{0, 0};
		fVector divided = {
			x / rhs,
			y / rhs
		};
		return divided;
	}
	fVector operator*(const float &rhs) 
	{
		return fVector { x * rhs, y * rhs };
	};
	fVector operator+(const fVector &rhs) 
	{
		return fVector { x + rhs.x, y + rhs.y };
	};
	fVector operator-(const fVector &rhs) 
	{
		return fVector { x - rhs.x, y - rhs.y };
	};
	fVector& operator+=(const fVector &rhs) {
		this -> x += rhs.x;
		this -> y += rhs.y;
		return *this;
	};
	

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
		MovingEntity() {
			velocity = { 1, 0 };
			heading = { 1, 0 };
			side = { 0, -1 };
			position = { 300, 300 };
		};

		void render(SDL_Renderer *renderer) {
			SDL_Point points[] = {
				{ position.x + heading.x * 15, position.y + heading.y * 15 },
				{ position.x + side.x * 5, position.y + side.y * 5 },
				{ position.x - side.x * 5, position.y - side.y * 5 },
				{ position.x + heading.x * 15, position.y + heading.y * 15 }
			};
			int count = 4; 
			SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255); // SET SCREEN TO BLACK
			SDL_RenderDrawLines(renderer, points, count);
		};
};

class Vehicle : public MovingEntity
{
	private:
		// pointer to game world

		// SteeringBehaviours* steering;
	public:
		void update(float elapsed_time) {
			fVector steeringForce_ = { 1, 0 };
			// = steering -> calculate();
			fVector acceleration_ = steeringForce_ / mass;
			velocity += acceleration_ * elapsed_time;
			velocity.truncate(maxSpeed);
			position += velocity * elapsed_time;
// 
			if(position.x > 960) position.x -= 960;
			
			if(velocity.lengthSq() > 0.00000001)
			{
				heading = velocity.getNormalized();
				side = heading.getPerp();
			}
		}
};

		
			
