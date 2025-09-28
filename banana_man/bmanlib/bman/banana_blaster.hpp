#ifndef BLASTER_HPP
#define BLASTER_HPP

#include <raylib.h>

struct BananaBlaster {
    // Constructor - Laser - Takes Vector and int
    BananaBlaster(Vector2 position, int speed);
    // Function to update laser position
    void update();
    // Function to draw lasers to screen, handled with raylib
    void draw();
    // Function to get rectangle for lasers
    Rectangle get_rect();
    bool active;
    Vector2 position;
    int speed;
};

#endif