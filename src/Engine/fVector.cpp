#include "./fVector.h"
#include <cmath>

// GETTERS
fVector fVector::getNormal() {
	float h = getLength();
	return fVector { x / h, y / h };
}
fVector fVector::getPerpendicular() { return fVector { y, -x }; }
float fVector::getLength() { return sqrt( x*x + y*y ); }
float fVector::getLengthSq() { return x * x + y * y; }

// MODIFIERS
void fVector::normalize()
{
	float h = getLength();
	x /= h;
	y /= h;
}
void fVector::truncate(float maxValue) 
{
	if(maxValue * maxValue < x * x + y * y) {
		const float h = getLength();
		x /= h;
		y /= h;
		x *= maxValue;
		y *= maxValue;
	};
}

// SETTERS
void fVector::setMagnitude(float mag) 
{
	const float scalar = getLength();
	x = x / scalar * mag;
	y = y / scalar * mag;
}


// OPERATOR OVERLOADING
fVector fVector::operator/(const float &rhs) 
{ 
	if(rhs==0) return fVector{0, 0}; 
	return fVector { x / rhs, y / rhs };
}
fVector fVector::operator*(const float &rhs) {return fVector { x * rhs, y * rhs }; };
fVector fVector::operator+(const fVector &rhs) { return fVector { x + rhs.x, y + rhs.y }; };
fVector fVector::operator-(const fVector &rhs) { return fVector { x - rhs.x, y - rhs.y }; };
fVector& fVector::operator=(const fVector &rhs) 
{
	this -> x = rhs.x;
	this -> y = rhs.y;
	return *this;
}
fVector& fVector::operator+=(const fVector &rhs) 
{
	this -> x += rhs.x;
	this -> y += rhs.y;
	return *this;
}
