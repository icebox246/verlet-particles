#ifndef __LA_H
#define __LA_H

typedef struct {
    float x, y;
} V2;

V2 v2(float x, float y);
V2 v2zero();
V2 v2add(V2 a, V2 b);
V2 v2sub(V2 a, V2 b);
V2 v2mult(V2 a, V2 b);
V2 v2scale(V2 a, float c);
float v2len(V2 a);
V2 v2perp(V2 a);
V2 v2norm(V2 a);

float sigf(float a);

#endif
