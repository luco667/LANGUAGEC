#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fenetre.h"

int myFenetre(void) {
	
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("%s\n", SDL_GetError());
        exit(-1);
    } else if (TTF_Init() < 0) {  // Initialiser SDL_ttf
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(-1);
    }

	printf("it's work \n");
		
  return 0;
}