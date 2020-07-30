#pragma once

struct fVector {
	float x;
	float y;

	// getters
	fVector getNormal();
	fVector getPerpendicular();
	float getLength();
	float getLengthSq();

	// modifiers
	void normalize(); 
	void truncate(float maxValue);
	void setMagnitude(float mag);

	// operator overloading
	fVector operator/(const float &rhs);
	fVector operator*(const float &rhs); 
	fVector operator+(const fVector &rhs); 
	fVector operator-(const fVector &rhs); 
	fVector& operator=(const fVector &rhs);
	fVector& operator+=(const fVector &rhs);
};
