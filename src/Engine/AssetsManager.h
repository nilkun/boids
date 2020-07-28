#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "./nilkun.h"
#include "./Camera.h"
#include "../Enums.h"

void message(const char* title, const char* text, Uint32 flag = SDL_MESSAGEBOX_ERROR) ;

class SpriteSheet {
	private:
		SDL_Texture* sheet;
	public:
		std::vector<int> animations;
};

class Animation {
	public:
		SDL_Rect frame;
		Animation(SDL_Rect f) : frame(f) {};
		SDL_Point offset_; 
		float current_frame = 0;
		float playback_speed = 4.5;
		size_t frame_count = 10;
		void update(float delta) {
			// looping
			current_frame += delta / 1000 * playback_speed;
			if(current_frame >= frame_count) current_frame -= frame_count;
			frame.x = static_cast<int>(current_frame) * frame.w;
		}
};

class AssetsManager {
	private:
		SDL_Renderer * renderer;

		public:
		size_t ID = 0;
		size_t scalar = 4;
		SDL_Rect index = { 0, 0, 7, 12 };
		std::unordered_map<size_t, SDL_Texture *> textures;
		SDL_Rect target = { 50, 50, static_cast<int> ( 7 * scalar ), static_cast<int>( 12 * scalar ) };

	public:
		size_t create(const char* filename);
		AssetsManager(SDL_Renderer *r) {
			renderer = r;
		};
		void doso() { };
};

// TODO
// DIRECTION OF PLAYER
// 1. Camera follow player
// 2. Add limits
// 3. Add puck
// 4. Player can control puck
// 5. Player can dispose puck
// 6. Add goal
// 7. Add shooting
// 8. Add scoreboard
// 9. Add players
// 10. Add faceoff
// 11. Add goalies
// 12. Add FSM
struct background {
	SDL_Texture * texture;
};

class AnimatedSprite {
	SDL_Rect index;
	size_t frames;
};
class Spritesheet {
	private:
		SDL_Texture *spritesheet;
};

