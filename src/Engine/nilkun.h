#pragma once
#include <random>

namespace nilkun {
	uint32_t Lehmer32();
	int random(int min, int max);
	//float random(float min, float max);
	int min(int val1, int val2);
	struct Point { float x, y; };
	struct PPoint { float *x, *y; };
	struct Position { 
		float x, y, w, h; 
		Position(){};
		Position(float x, float y, float w, float h) : x(x), y(y), w(w), h(h){};
		Position(const nilkun::Position &pos);
		Position operator-(const Position &rhs);
	};
};
