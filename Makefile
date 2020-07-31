UPDATING=
MAIN=
ALLFILES= ./src/main.cpp ./src/Engine/AssetsManager.cpp ./src/Engine/ScreenManager.cpp ./src/Engine/nilkun.cpp ./src/Units/MovingEntity.cpp ./src/Engine/fVector.cpp ./src/Units/Vehicle.cpp
#./src/GameObjects/Map.cpp ./src/GameObjects/Player.cpp ./src/GameObjects/Monsters.cpp ./src/nilkun.cpp ./src/Camera.cpp ./src/RenderableObject.cpp ./src/Animation.cpp ./src/Texture.cpp
TARGETFILE=boids
LFLAGS= 
# -Wall
CFLAGS=-lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf
COMPILER=g++

# emscriptem
#MAIN=./src/emscripten.cpp ./src/Game.cpp
CFLAGS=-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file resources
COMPILER=emcc
TARGETFILE=wasm/game.html

all:
	$(COMPILER) $(LFLAGS) -o $(TARGETFILE) $(MAIN) $(ALLFILES) $(GAMEENGINE) $(UPDATING) $(CFLAGS)
