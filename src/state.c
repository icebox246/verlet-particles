#include "state.h"

void loop(void* _state) {
    State* state = (State*)_state;
    // calculate dt
    float dt = (SDL_GetTicks64() - state->lastTime) / 1000.;
    state->lastTime = SDL_GetTicks64();

    // events
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_QUIT: {
                state->quitting = 1;
            } break;
            case SDL_MOUSEBUTTONDOWN: {
                if (ev.button.button == SDL_BUTTON_LEFT) {
                    state->clickCount++;
                    switch (state->clickCount) {
                        case 1:
                            state->lastClick = v2(ev.button.x, ev.button.y);
                            break;
                        case 2:
                            state->clickCount = 0;
                            V2 p2 = v2(ev.button.x, ev.button.y);
                            state->lines[state->lineCount++] =
                                create_line(state->lastClick, p2);
                            break;
                    }
                }
                if (ev.button.button == SDL_BUTTON_RIGHT) {
                    state->clickCount = 0;
                    state->bodies[state->bodyCount++] = create_body(
                        v2(ev.button.x, ev.button.y), rand() % 10 + 10);
                }
            } break;
            case SDL_MOUSEMOTION: {
                state->mousePos = v2(ev.motion.x, ev.motion.y);
            } break;
        }
    }

    // process
    V2 gravity = v2(0, 100);

    int steps = 10;
    float sdt = dt / steps;

    for (int step = 0; step < steps; step++) {
        for (size_t i = 0; i < state->bodyCount; i++) {
            accelerate_body(&state->bodies[i], gravity);
            rect_constrain_body(&state->bodies[i], v2(0, 0),
                                v2(WINDOW_WIDTH, WINDOW_HEIGHT));
            for (int j = 0; j < state->lineCount; j++) {
                line_constrain_body(&state->bodies[i], state->lines[j]);
            }
            collide_bodies_body(&state->bodies[i], state->bodies,
                                state->bodyCount);
            update_body(&state->bodies[i], sdt);
        }
    }

    // render

    SDL_SetRenderDrawColor(state->renderer, 10, 10, 10, 255);
    SDL_RenderClear(state->renderer);

    for (size_t i = 0; i < state->bodyCount; i++) {
        draw_body(&state->bodies[i], state->renderer);
    }

    SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, 255);

    for (int i = 0; i < state->lineCount; i++) {
        draw_line(&state->lines[i], state->renderer);
    }

    if (state->clickCount == 1) {
        SDL_RenderDrawLineF(state->renderer, state->lastClick.x,
                            state->lastClick.y, state->mousePos.x,
                            state->mousePos.y);
    }

    SDL_RenderPresent(state->renderer);
    SDL_Delay(5);
}
