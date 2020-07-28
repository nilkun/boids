#include "AssetsManager.h"
#include <SDL2/SDL_image.h>
#include <iostream>

void message(const char* title, const char* text, Uint32 flag) {
	SDL_ShowSimpleMessageBox(flag, title, text, NULL);
};

size_t AssetsManager::create(const char* filename) {
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filename);

	if(surface == NULL) message("Error Loading Image", filename);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(texture == NULL)	message("Error creating texture", filename);
	textures.insert(std::pair<size_t, SDL_Texture*>(ID, texture));
	SDL_FreeSurface(surface);
	return ID++;
};
