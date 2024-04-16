#ifndef MAIN_H_   /* Include guard */
#define MAIN_H_

void quitProgram(SDL_Renderer *renderer, SDL_Window *window) {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

#endif 