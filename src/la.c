#include "la.h"

#include <math.h>

#include "line.h"

V2 v2(float x, float y) {
    V2 res = {.x = x, .y = y};
    return res;
}

V2 v2zero() { return v2(0, 0); }

V2 v2add(V2 a, V2 b) {
    V2 res = {.x = a.x + b.x, .y = a.y + b.y};
    return res;
}

V2 v2sub(V2 a, V2 b) {
    V2 res = {.x = a.x - b.x, .y = a.y - b.y};
    return res;
}

V2 v2mult(V2 a, V2 b) {
    V2 res = {.x = a.x * b.x, .y = a.y * b.y};
    return res;
}

V2 v2scale(V2 a, float c) {
    V2 res = {.x = a.x * c, .y = a.y * c};
    return res;
}

float v2len(V2 a) { return (float)sqrt(a.x * a.x + a.y * a.y); }

V2 v2perp(V2 a) {
    V2 res = {.x = a.y, .y = -a.x};
    return res;
}

V2 v2norm(V2 a) { return v2scale(a, 1.0 / v2len(a)); }


float sigf(float a) { return (a > 0) ? 1 : ((a < 0) ? -1 : 0); }

