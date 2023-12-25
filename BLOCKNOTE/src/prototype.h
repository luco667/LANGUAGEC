#ifndef PROTOTYPE_H_   /* Include guard */
#define PROTOTYPE_H_

// Function prototypes

const int WIDTH = 1000;
const int HEIGHT = 1000;
const int POSITION_X = 100;
const int POSITION_Y = 100;
const int ERASE_RADIUS = 20;

typedef struct RectanglesElement {
    SDL_Rect data;
    SDL_Color color;
    struct RectanglesElement *next;
} RectanglesElement;

typedef struct Button {
    SDL_Rect rect;
    bool active;
} Button;


typedef struct TextBox {
    SDL_Rect rect;
    SDL_Color color;
    char text[50]; // Texte à afficher
} TextBox;

int pixelWidth = 10;
int pixelHeight = 10;

RectanglesElement *lastAddedRect = NULL;

RectanglesElement *createRectangleElement(SDL_Rect rect, SDL_Color color);
void insertBeginning(RectanglesElement **rectangles, SDL_Rect rect, SDL_Color color);
void insertEnd(RectanglesElement **rectangles, SDL_Rect rect, SDL_Color color);
void freeRectangles(RectanglesElement *rectangles);
void drawRectangles(SDL_Renderer *renderer, RectanglesElement *rectangles);
void eraseRectanglesAroundMouse(RectanglesElement **rectangles, int mouseX, int mouseY);
void increasePixelSize();
void reducePixelSize();
void quitProgram(SDL_Renderer *renderer, SDL_Window *window, RectanglesElement *rectangles);
bool isMouseInsideButton(Button *button, int mouseX, int mouseY);
double distance(int x1, int y1, int x2, int y2);

void takeScreenshot(SDL_Renderer *renderer, SDL_Window *window) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char filename[100];
    snprintf(filename, sizeof(filename), "screenshot_%d-%02d-%02d_%02d-%02d-%02d.bmp",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
             tm.tm_hour, tm.tm_min, tm.tm_sec);

    SDL_Surface *screenshot = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32,
                                                   0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels, screenshot->pitch);

    SDL_SaveBMP(screenshot, filename);

    SDL_FreeSurface(screenshot);

    printf("Screenshot saved as %s\n", filename);
}
//under last return

RectanglesElement *createRectangleElement(SDL_Rect rect, SDL_Color color) {
    RectanglesElement *newElement = (RectanglesElement *)malloc(sizeof(RectanglesElement));
    newElement->next = NULL;
    newElement->data = rect;
    newElement->color = color;
    return newElement;
}

void insertBeginning(RectanglesElement **rectangles, SDL_Rect rect, SDL_Color color) {
    RectanglesElement *newElement = createRectangleElement(rect, color);
    newElement->next = *rectangles;
    *rectangles = newElement;
}

void insertEnd(RectanglesElement **rectangles, SDL_Rect rect, SDL_Color color) {
    RectanglesElement *newElement = createRectangleElement(rect, color);
    newElement->next = NULL;

    if (*rectangles == NULL) {
        *rectangles = newElement;
        return;
    }

    RectanglesElement *last = *rectangles;

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newElement;
}

void freeRectangles(RectanglesElement *rectangles) {
    RectanglesElement *current = rectangles;
    RectanglesElement *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void drawRectangles(SDL_Renderer *renderer, RectanglesElement *rectangles) {
    RectanglesElement *pt;

    for (pt = rectangles; pt != NULL; pt = pt->next) {
        SDL_SetRenderDrawColor(renderer, pt->color.r, pt->color.g, pt->color.b, pt->color.a);
        SDL_RenderFillRect(renderer, &pt->data);
    }
}

void eraseRectanglesAroundMouse(RectanglesElement **rectangles, int mouseX, int mouseY) {
    RectanglesElement *current = *rectangles;
    RectanglesElement *prev = NULL;

    while (current != NULL) {
        int rectX = current->data.x + current->data.w / 2;
        int rectY = current->data.y + current->data.h / 2;

        int dist = distance(rectX, rectY, mouseX, mouseY);

        if (dist <= ERASE_RADIUS) {
            if (prev == NULL) {
                *rectangles = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            current = prev == NULL ? *rectangles : prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void increasePixelSize() {
    pixelWidth += 5;
    pixelHeight += 5;
}

void reducePixelSize() {
    pixelWidth = (pixelWidth > 5) ? pixelWidth - 5 : 5;
    pixelHeight = (pixelHeight > 5) ? pixelHeight - 5 : 5;
}
void textyping() {
	
}

void quitProgram(SDL_Renderer *renderer, SDL_Window *window, RectanglesElement *rectangles) {
    freeRectangles(rectangles);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

bool isMouseInsideButton(Button *button, int mouseX, int mouseY) {
    return (mouseX >= button->rect.x && mouseX <= button->rect.x + button->rect.w &&
            mouseY >= button->rect.y && mouseY <= button->rect.y + button->rect.h);
}

double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

#endif 