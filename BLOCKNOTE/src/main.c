#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <time.h> // Pour générer un nom de fichier unique
#include "prototype.h"


int main(int argc, char *argv[]) {
	
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("%s\n", SDL_GetError());
        exit(-1);
    }

    RectanglesElement *rectangles = NULL;
    SDL_Window *window = SDL_CreateWindow("NOTEBLOCK SDL2", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        printf("%s\n", SDL_GetError());
        exit(-1);
    } /*else if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(-1);
    }
*/
    SDL_Event windowEvent;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
	
    SDL_Color currentColor = {rand() % 256, rand() % 256, rand() % 256, 255};
    SDL_Color plusButtonColor = {0, 0, 255, 255};
    SDL_Color minusButtonColor = {255, 0, 0, 255};
    SDL_Color colorButtonColor = {0, 255, 0, 255};
    SDL_Color windowColor = {255, 255, 0, 255};

    Button plusButton = {{10, 10, 30, 30}, false};
    Button minusButton = {{50, 10, 30, 30}, false};
    Button colorButton = {{90, 10, 30, 30}, false};
	 Button textBoxButton = {{130, 10, 50, 30}, false}; // Bouton pour créer une zone de texte

    while (1) {
        while (SDL_PollEvent(&windowEvent)) {
            switch (windowEvent.type) {
                case SDL_QUIT:
                    quitProgram(renderer, window, rectangles);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (isMouseInsideButton(&plusButton, windowEvent.button.x, windowEvent.button.y)) {
                        plusButton.active = true;
                    } else if (isMouseInsideButton(&minusButton, windowEvent.button.x, windowEvent.button.y)) {
                        minusButton.active = true;
                    } else if (isMouseInsideButton(&colorButton, windowEvent.button.x, windowEvent.button.y)) {
                        colorButton.active = true;
                    } else if (windowEvent.button.button == SDL_BUTTON_LEFT) {
                        SDL_Rect rect = {windowEvent.button.x, windowEvent.button.y, pixelWidth, pixelHeight};    
                    } break;

                case SDL_MOUSEBUTTONUP:
                    if (isMouseInsideButton(&plusButton, windowEvent.button.x, windowEvent.button.y)) {
                        if (plusButton.active) {
                            increasePixelSize();
                            plusButton.active = false;
                        }
                    } else if (isMouseInsideButton(&minusButton, windowEvent.button.x, windowEvent.button.y)) {
                        if (minusButton.active) {
                            reducePixelSize();
                            minusButton.active = false;
                        }
                    } else if (isMouseInsideButton(&colorButton, windowEvent.button.x, windowEvent.button.y)) {
                        if (colorButton.active) {
                            windowColor.r = rand() % 256;
                            windowColor.g = rand() % 256;
                            windowColor.b = rand() % 256;
                            colorButton.active = false;
                        }
                    } else if (windowEvent.button.button == SDL_BUTTON_MIDDLE) {
                        // ...
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
                        eraseRectanglesAroundMouse(&rectangles, windowEvent.motion.x, windowEvent.motion.y);
                    } else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                        SDL_Rect rect = {windowEvent.motion.x, windowEvent.motion.y, pixelWidth, pixelHeight};
                        insertBeginning(&rectangles, rect, currentColor);
                    } else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
                        SDL_Rect rect = {windowEvent.motion.x, windowEvent.motion.y, pixelWidth, pixelHeight};
                        insertEnd(&rectangles, rect, currentColor);
                    } /*else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                            insertBeginning(&rectangles, rect, currentColor);
                        } else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
                            insertEnd(&rectangles, rect, currentColor);
                        } else if (windowEvent.button.button == SDL_BUTTON_MIDDLE) {
                        eraseRectanglesAroundMouse(&rectangles, windowEvent.motion.x, windowEvent.motion.y);
                        }*/ break;

                    if (colorButton.active) {
                        SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
                        SDL_RenderClear(renderer);
                        drawRectangles(renderer, rectangles);

                        SDL_SetRenderDrawColor(renderer, plusButtonColor.r, plusButtonColor.g, plusButtonColor.b, plusButtonColor.a);
                        SDL_RenderFillRect(renderer, &plusButton.rect);

                        SDL_SetRenderDrawColor(renderer, minusButtonColor.r, minusButtonColor.g, minusButtonColor.b, minusButtonColor.a);
                        SDL_RenderFillRect(renderer, &minusButton.rect);

                        SDL_SetRenderDrawColor(renderer, colorButtonColor.r, colorButtonColor.g, colorButtonColor.b, colorButtonColor.a);
                        SDL_RenderFillRect(renderer, &colorButton.rect);

                        SDL_RenderPresent(renderer);
                    } else {
						
					}
                    break;

                case SDL_KEYDOWN:
                    if (windowEvent.key.keysym.sym == SDLK_SPACE) {
                        currentColor.r = rand() % 256;
                        currentColor.g = rand() % 256;
                        currentColor.b = rand() % 256;
                    } else if (windowEvent.key.keysym.sym == SDLK_e) {
						takeScreenshot(renderer, window);
					} else if (windowEvent.key.keysym.sym == SDLK_a) {
						textyping();
					}
                    break;
            }
        }

        if (!plusButton.active && !minusButton.active && !colorButton.active) {
            SDL_SetRenderDrawColor(renderer, windowColor.r, windowColor.g, windowColor.b, windowColor.a);
            SDL_RenderClear(renderer);
            drawRectangles(renderer, rectangles);

            SDL_SetRenderDrawColor(renderer, plusButtonColor.r, plusButtonColor.g, plusButtonColor.b, plusButtonColor.a);
            SDL_RenderFillRect(renderer, &plusButton.rect);

            SDL_SetRenderDrawColor(renderer, minusButtonColor.r, minusButtonColor.g, minusButtonColor.b, minusButtonColor.a);
            SDL_RenderFillRect(renderer, &minusButton.rect);

            SDL_SetRenderDrawColor(renderer, colorButtonColor.r, colorButtonColor.g, colorButtonColor.b, colorButtonColor.a);
            SDL_RenderFillRect(renderer, &colorButton.rect);

            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}
