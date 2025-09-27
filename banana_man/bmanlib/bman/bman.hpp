#ifndef BMAN_HPP
#define BMAN_HPP

#include <raylib.h>

struct BananaMan {
    BananaMan();
    void draw();
    void update();
    void keyboard();
    Rectangle get_rect();
    bool grounded;
    bool dj;
    Vector2 pos;
    Vector2 size;
    Vector2 velocity;
    float gravity;
    float speed;
    void double_jump();
};

#endif