#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fenetre.h"


int main(int argc, char *argv[]) {
	
		SDL_Window *window = SDL_CreateWindow("NOTEBLOCK SDL2", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_Event windowEvent;
		
		

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("%s\n", SDL_GetError());
        exit(-1);
    } else if (TTF_Init() < 0) {  // Initialiser SDL_ttf
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(-1);
    } else if (window == NULL) {
        printf("%s\n", SDL_GetError());
        exit(-1);
    } 
		printf("it's work \n");
		

		while (1) {
        while (SDL_PollEvent(&windowEvent)) {
			
		SDL_SetRenderDrawColor(renderer, colorrendererX, colorrendererY, colorrendererZ, colorrendererL);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		void quitProgram(SDL_Renderer *renderer, SDL_Window *window);
			switch (windowEvent.type) {

                case SDL_QUIT:
                    printf("its quit \n");
                    quitProgram(renderer, window);
                    break;
			}
		}

		}
  return 0;
}
