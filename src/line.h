#ifndef __LINE_H
#define __LINE_H

#include "la.h"
#include <SDL2/SDL_render.h>

typedef struct {
    V2 a, b;
} Line;

float dist_line_point(V2 p, Line l);
V2 closest_line_point(V2 p, Line l);
void draw_line(Line* line, SDL_Renderer* renderer);
V2 line_to_vec(Line line);
float line_len(Line line);

Line create_line(V2 a, V2 b);

#endif
