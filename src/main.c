#include <SDL2/SDL.h>
#include <stdio.h>

#include "state.h"

#if __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main(void) {
    State state = {0};

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "ParticleSim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALWAYS_ON_TOP);

    state.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    init_body_system(state.renderer);

    printf("[INFO] Initialised...\n");

    state.lastTime = SDL_GetTicks64();

#if __EMSCRIPTEN__
    emscripten_set_main_loop_arg(loop, &state, 120, 1);
#else
    while (!state.quitting) {
        loop(&state);
    }
#endif

    printf("[INFO] Shutting down...\n");
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
