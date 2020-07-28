#include <SDL2/SDL.h>

// HELPERS
#include "./Engine/ScreenManager.h"

// GAME OBJECTS
#include "./Engine/AssetsManager.h"
#include "./Controls/UserInput.h"
#include "./Units/MovingEntity.h"
// STD
#include <algorithm>

const int SCREENWIDTH = 960;
const int SCREENHEIGHT = 540;

int main() 
{
	// Create Screen
	Screen *screen;
	SDL_Renderer* renderer;

   	screen = Screen::instance();
	screen -> init("Boids", SCREENWIDTH, SCREENHEIGHT);
	renderer = screen -> getRenderer();
	
	UserInput userInput;
	// Game mechanics
	bool running = true;

	// Assets Manager
	AssetsManager *am = new AssetsManager(renderer);
	// am -> create("resources/player_sprites.png");

	Vehicle ship;

	while(running) {
		
		// Users input
		running = userInput.read();
		ship.update(0.016);	
		// Rendering
		screen -> clear();
		ship.render(renderer);
		screen -> render();
	}
	screen -> close();
}
