#include <SDL2/SDL.h>
#include <vector>

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
	// AssetsManager *am = new AssetsManager(renderer);
	// am -> create("resources/player_sprites.png");

	// std::vector<Vehicle> ships(20);
	Flock *flock = new Flock();

	while(running) {
		
		// Users input
		running = userInput.read();
		flock -> update(16);
		// Rendering
		screen -> clear();
		flock -> render(renderer);
		screen -> render();
	}
	delete flock;
	screen -> close();
	return 1;
}
