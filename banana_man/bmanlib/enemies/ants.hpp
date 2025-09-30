#ifndef ANTS_HPP
#define ANTS_HPP

#include <raylib.h>
#include <vector>

struct Ants {
    Ants(Vector2 pos, Vector2 size);
    void draw();
    Rectangle get_rect();
    void fire_laser(int dir);

    Vector2 pos;
    Vector2 size;
    int health;
};

#endif