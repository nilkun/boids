UPDATING=
MAIN=
ALLFILES= ./src/main.cpp ./src/Engine/AssetsManager.cpp ./src/Engine/ScreenManager.cpp ./src/Engine/nilkun.cpp ./src/Units/MovingEntity.cpp ./src/Engine/fVector.cpp ./src/Units/Vehicle.cpp

EM_TARGETFILE=wasm/game.html
EM_LFLAGS=-std=c++14 -Wno-all
EM_CFLAGS=-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' 
# --preload-file resources
EM_COMPILER=emcc

LI_TARGETFILE=boids
LI_LFLAGS=-Wall
LI_CFLAGS=-lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf
LI_COMPILER=g++

linux: COMPILER=${LI_COMPILER} 
linux: TARGETFILE=${LI_TARGETFILE} 
linux: LFLAGS=${LI_LFLAGS} 
linux: CFLAGS=${LI_CFLAGS} 
em:	COMPILER=${EM_COMPILER} 
em: TARGETFILE=${EM_TARGETFILE} 
em: LFLAGS=${EM_LFLAGS} 
em: CFLAGS=${EM_CFLAGS}
linux em:
	$(COMPILER) $(LFLAGS) -o $(TARGETFILE) $(MAIN) $(ALLFILES) $(GAMEENGINE) $(UPDATING) $(CFLAGS)
