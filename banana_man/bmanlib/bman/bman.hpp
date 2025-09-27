#ifndef BMAN_HPP
#define BMAN_HPP

#include <algorithm>
#include <raylib.h>

struct BananaMan {
    BananaMan(Vector2 size);
    void draw();
    void update();
    void keyboard(float dt);
    Rectangle get_rect();
    Rectangle get_prev_rect();
    bool grounded;
    bool can_double;
    Vector2 pos;
    Vector2 prev_pos;
    Vector2 size;
    Vector2 velocity;
    float gravity;
    float speed;
    float restitution;
    float jump_velocity;
    float jump_buffer;
    float coyote;
};

#endif