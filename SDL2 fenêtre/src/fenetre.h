#ifndef FENETRE_H_   /* Include guard */
#define FENETRE_H_

static int WIDTH = 500;
static int HEIGHT = 500;
static int POSITION_X = 100;
static int POSITION_Y = 100;

static int colorrendererX = 255;
static int colorrendererY = 255;
static int colorrendererZ = 0;
static int colorrendererL = 150;

	

	
void quitProgram(SDL_Renderer *renderer, SDL_Window *window) {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}


#endif 