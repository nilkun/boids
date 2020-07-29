#include "./nilkun.h"
#include <iostream>
#include <time.h>

// #include <random>

namespace nilkun {
    static uint32_t nLehmer = time(NULL);
	uint32_t Lehmer32() {
		nLehmer += 0xe120fc15;
		uint64_t tmp;
		tmp = (uint64_t)nLehmer * 0x4a39b70d;
		uint32_t m1 = (tmp >> 32) ^ tmp;
		tmp = (uint64_t)m1 * 0x12fad5c9;
		uint32_t m2 = (tmp >> 32) ^ tmp;
		return m2;
	};

	int random(const int min, const int max) { 
		int val = min + Lehmer32() % (max - min); 
			//min + (r() % (max - min)); 
		return val; 
	};
	//float random(float min, float max) { return max - min; }; // placeholder
	// ((float)

	int min(int val1, int val2) { return val1 < val2 ? val1 : val2; };
	Position::Position(const nilkun::Position &pos) {
		x = pos.x;
		y = pos.y;
		w = pos.w;
		h = pos.h;
	};
	Position Position::operator-(const Position &rhs) {
		Position pos{
			this ->x - rhs.x, 
			this ->y - rhs.y, 
			this ->w - rhs.w, 
			this ->h - rhs.h
			};
		return pos;
	};
};
