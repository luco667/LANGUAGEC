#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fenetre.h"
#include "pixels.h"
#include "main.h"

int main(int argc, char *argv[]) {
	
		SDL_Window *window = SDL_CreateWindow("NOTEBLOCK SDL2", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_Event windowEvent;
		myFenetre();
	
	while (1) {
        while (SDL_PollEvent(&windowEvent)) {
			
		SDL_SetRenderDrawColor(renderer, colorrendererX, colorrendererY, colorrendererZ, colorrendererL);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		
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
