UPDATING=
MAIN=
ALLFILES= ./src/main.cpp ./src/Engine/AssetsManager.cpp ./src/Engine/ScreenManager.cpp ./src/Engine/nilkun.cpp ./src/Units/MovingEntity.cpp ./src/Engine/fVector.cpp ./src/Units/Vehicle.cpp

linux:
	TARGETFILE=boids
	LFLAGS=-Wall
	CFLAGS=-lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf
	COMPILER=g++

# emscriptem
em:
	CFLAGS=-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' 
	# --preload-file resources
	COMPILER=emcc
	TARGETFILE=wasm/game.html
	LFLAGS= -std=c++14 -Wno-all

all:
	$(COMPILER) $(LFLAGS) -o $(TARGETFILE) $(MAIN) $(ALLFILES) $(GAMEENGINE) $(UPDATING) $(CFLAGS)
