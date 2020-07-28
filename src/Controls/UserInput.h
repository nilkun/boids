#pragma once
#include <SDL2/SDL.h>

class UserInput {
	private:
		SDL_Event event;
	public:
		bool read() {
			const Uint8* keystate = SDL_GetKeyboardState(NULL);

			// Polling
			if(keystate[SDL_SCANCODE_Q]) return false; 

			while(SDL_PollEvent(&event))
			{
				switch (event.type) {
					case SDL_QUIT:
						return false;
						break;
				}
			}
			return true;
		};
};
