#pragma once
#include <SDL2/SDL.h>
#include "nilkun.h"
#include <iostream>
#include "../Constants.h"

// Provide screen resolution
// and scale
//
//
class Camera {
	public:
		// Camera top left position
		SDL_Point position { 0, 0 };
		// Camera viewport size
		SDL_Point size { 960 / 4, 540 / 4 };	
		// Camera screen center
		SDL_Point center { size.x / 2, size.y / 2 };
		// Camera target
		nilkun::Position *target; 
		// UPPER LIMIT
		nilkun::Point max_pos;
		// Zoom
		SDL_Rect getPosition(nilkun::Position &pos) {
			SDL_Rect point { 
					static_cast<int>((pos.x - position.x) * Constants::SCALE),
					static_cast<int>((pos.y - position.y) * Constants::SCALE),
					static_cast<int>(pos.w * Constants::SCALE),
					static_cast<int>(pos.h * Constants::SCALE)
			};
			return point;
		};
		float zoom = 4;

		// FOR TESTING
		float width = 267 * Constants::SCALE;
		float height = 150 * Constants::SCALE;
		float vV = 267;
			//960 / Constants::SCALE;
		// 420 288 is the texture size
		float vH = 150;
		//540 / Constants::SCALE;
		float cX = vV / 2;
		float cY = vH / 2;

		SDL_Rect pan() {
			// SDL_Point size { 
			SDL_Rect point {
				position.x,
				position.y,
				static_cast<int>(vV),
				static_cast<int>(vH)
			};
			// std::cout << position.x << "x" << position.y << "x" << vV << "x" << vH << std::endl;
			return point;
		};

	public:	
		Camera();
		// Camera(size_t width, size_t height) : size.x(width), size.y(height) {};
		Camera(size_t width, size_t height) { size.x = width; size.y = height; };
		Camera(nilkun::Position *position);
		void setTarget(nilkun::Position* position);
		void update();
		void setLimits(float w, float h, nilkun::Point *world_size);
		SDL_Rect getRenderTargetPosition(const nilkun::Position& pos) {
			// SDL_Rect position(pos);
			// position *= Constants::SCALE;
			SDL_Rect point { 
					static_cast<int>((pos.x - position.x) * Constants::SCALE),
					static_cast<int>((pos.y - position.y - pos.h) * Constants::SCALE),
					static_cast<int>(pos.w * Constants::SCALE),
					static_cast<int>(pos.h * Constants::SCALE)
			};
			return point;
		}
};
