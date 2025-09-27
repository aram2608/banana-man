#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <raylib.h>

struct Platform {
    Platform(Vector2 pos, Vector2 size);
    void draw() const;
    Rectangle get_rect() const;
    Vector2 pos;
    Vector2 size;
};

#endif