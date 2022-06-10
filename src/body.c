#include "body.h"

#include <assert.h>

static SDL_Texture* bodyTex;

int init_body_system(SDL_Renderer* renderer) {
    const size_t size = 256;

    int r = size / 2;

    bodyTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                SDL_TEXTUREACCESS_TARGET, size, size);

    SDL_SetTextureBlendMode(bodyTex, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, bodyTex);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if ((x - r) * (x - r) + (y - r) * (y - r) <= r * r)
                SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    return 0;
}

Body create_body(V2 position, float rad) {
    Body body = {.currentPos = position, .lastPos = position, .radius = rad};

    return body;
}

void update_body(Body* body, float dt) {
    V2 newPos = v2add(v2sub(v2scale(body->currentPos, 2), body->lastPos),
                      v2scale(body->acceleration, dt * dt));

    body->acceleration = v2zero();
    body->lastPos = body->currentPos;
    body->currentPos = newPos;
}

void draw_body(Body* body, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_FRect rect = {.x = body->currentPos.x - body->radius,
                      .y = body->currentPos.y - body->radius,
                      .w = body->radius * 2,
                      .h = body->radius * 2};

    SDL_RenderCopyF(renderer, bodyTex, NULL, &rect);
}

void accelerate_body(Body* body, V2 a) {
    body->acceleration = v2add(body->acceleration, a);
}

void point_constrain_body(Body* body, V2 p) {
    V2 axis = v2sub(body->currentPos, p);
    float dst = v2len(axis);
    if (dst < body->radius) {
        body->currentPos = v2add(p, v2scale(axis, body->radius / dst));
    }
}

void line_constrain_body(Body* body, Line line) {
    point_constrain_body(body, line.a);
    point_constrain_body(body, line.b);

    V2 c = closest_line_point(body->currentPos, line);
    float dst = v2len(v2sub(body->currentPos, c));

    if (dst < body->radius &&
        fabsf(v2len(v2sub(line.a, c)) + v2len(v2sub(c, line.b)) -
              line_len(line)) <= 0.001f) {
        body->currentPos =
            v2add(c, v2scale(v2sub(body->currentPos, c), (body->radius) / dst));
    }
}

void rect_constrain_body(Body* body, V2 leftTop, V2 rightBottom) {
    // up
    line_constrain_body(body,
                        create_line(leftTop, v2(rightBottom.x, leftTop.y)));
    // right
    line_constrain_body(body,
                        create_line(v2(rightBottom.x, leftTop.y), rightBottom));
    // down
    line_constrain_body(body,
                        create_line(rightBottom, v2(leftTop.x, rightBottom.y)));
    // left
    line_constrain_body(body,
                        create_line(v2(leftTop.x, rightBottom.y), leftTop));
}

void collide_bodies_body(Body* body, Body* otherBodies, int bodyCnt) {
    for (int i = 0; i < bodyCnt; i++) {
        if (body == otherBodies + i) continue;
        V2 axis = v2sub(body->currentPos, otherBodies[i].currentPos);
        float dst = v2len(axis);
        float desired = body->radius + otherBodies[i].radius;
        if (dst < desired) {
            float delta = desired - dst;
            body->currentPos =
                v2add(body->currentPos, v2scale(axis, 0.5f * delta / dst));
            otherBodies[i].currentPos = v2add(
                otherBodies[i].currentPos, v2scale(axis, -0.5f * delta / dst));
        }
    }
}
