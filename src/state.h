#ifndef __STATE_H
#define __STATE_H

#include <stddef.h>

#include "body.h"
#include "la.h"
#include <SDL2/SDL.h>

#define MAX_BODIES 1024
#define MAX_LINES 1024

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 800

typedef struct {
    SDL_Renderer* renderer;

    size_t lastTime;

    size_t bodyCount;
    Body bodies[MAX_BODIES];

    int quitting;

    int clickCount;
    V2 lastClick;
    V2 mousePos;

    size_t lineCount;
    Line lines[MAX_LINES];
} State;

void loop(void* state);

#endif
