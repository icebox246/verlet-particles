#include "line.h"

Line create_line(V2 a, V2 b) {
    Line res = {.a = a, .b = b};
    return res;
}

void draw_line(Line* line, SDL_Renderer* renderer) {
    SDL_RenderDrawLineF(renderer, line->a.x, line->a.y, line->b.x, line->b.y);
}

float dist_line_point(V2 p, Line l) {
    return ((l.b.y - l.a.y) * p.x - (l.b.x - l.a.x) * p.y -
            (l.b.y - l.a.y) * l.b.x + (l.b.x - l.a.x) * l.b.y) /
           v2len(v2sub(l.b, l.a));
}

V2 closest_line_point(V2 p, Line l) {
    float a = l.b.y - l.a.y;
    float b = -(l.b.x - l.a.x);
    float c = -(l.b.x * a + l.b.y * b);

    return v2((b * (b * p.x - a * p.y) - a * c) / (a * a + b * b),
              (a * (-b * p.x + a * p.y) - b * c) / (a * a + b * b));
}

V2 line_to_vec(Line line) { return v2sub(line.b, line.a); }

float line_len(Line line) { return v2len(line_to_vec(line)); }
