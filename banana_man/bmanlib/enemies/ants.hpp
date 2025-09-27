#ifndef ANTS_HPP
#define ANTS_HPP

#include <raylib.h>

struct Ants {
    Ants(Vector2 pos);

    Vector2 pos;
    Vector2 size;
    int health;
};

#endif