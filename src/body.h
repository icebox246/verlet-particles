#ifndef __BODY_H
#define __BODY_H

#include <SDL2/SDL_render.h>

#include "la.h"
#include "line.h"

typedef struct {
    V2 currentPos, lastPos, acceleration;
    float radius;
} Body;

int init_body_system(SDL_Renderer* renderer);

Body create_body(V2 position, float rad);

void update_body(Body* body, float dt);

void draw_body(Body* body, SDL_Renderer* renderer);

void accelerate_body(Body* body, V2 a);

void line_constrain_body(Body* body, Line l);

void point_constrain_body(Body* body, V2 p);

void rect_constrain_body(Body* body, V2 leftTop, V2 rightBottom);

void collide_bodies_body(Body* body, Body* otherBodies, int bodyCnt);

#endif
