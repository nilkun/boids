#include <SDL2/SDL.h>
#include <vector>
#if EMSCRIPTEN
	#include <emscripten.h>
#endif

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

class Game {
	public:

	Screen *screen;
	SDL_Renderer* renderer;

	UserInput userInput;

	// Game mechanics
	bool running = true;
	
	// Assets Manager
	// AssetsManager *am = new AssetsManager(renderer);
	// am -> create("resources/player_sprites.png");
	
	Flock *flock;
	// std::vector<Vehicle> ships(20);
	void loop() {

	// while(running) {
			
		// Users input
		running = userInput.read();
		flock -> update(16);
		// Rendering
		screen -> clear();
		flock -> render(renderer);
		screen -> render();
	}
   	Game() {
		screen = Screen::instance();
		screen -> init("Boids", SCREENWIDTH, SCREENHEIGHT);
		renderer = screen -> getRenderer();
		flock = new Flock(SCREENWIDTH, SCREENHEIGHT);
	
	};
	~Game() {

		delete flock;
		screen -> close();
	};
};

Game game;
void runme() {
	game.loop();
};

int main() 
{
	// Create Screen


#if EMSCRIPTEN
	emscripten_set_main_loop(runme, -1, 1);
#else
	while(game.running) game.loop();	
#endif
	return 1;
}
