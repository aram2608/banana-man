#ifndef ANTBLASTER_HPP
#define ANTBLASTER_HPP

#include <cmath>
#include <raylib.h>

struct AntBlaster {
    // Constructor - Laser - Takes Vector and int
    AntBlaster(Vector2 position, int fire_pos, int speed);
    // Function to update laser position
    void update();
    // Function to draw lasers
    void draw();
    // Function to get rectangle for lasers
    Rectangle get_rect();
    bool active;
    Vector2 position;
    int speed;
    int fire_pos;
};

#endif