#include "bman/banana_blaster.hpp"

BananaBlaster::BananaBlaster(Vector2 position, int fire_pos, int speed)
    : position(position), fire_pos(fire_pos), speed(speed) {
    active = true;
}

// Function to draw BananaBlasters to screen, handled with raylib
void BananaBlaster::draw() {
    // Draw a 4x15 green BananaBlaster off the position of each instance of
    // BananaBlaster
    if (active)
        DrawRectangle(position.x, position.y, 15, 4, {255, 225, 53, 255});
}

// Function to get rectangle for BananaBlasters
Rectangle BananaBlaster::get_rect() {
    Rectangle rect;
    rect.x = position.x, rect.y = position.y, rect.width = 4;
    rect.height = 15;
    return rect;
}

// Function to update BananaBlaster position
void BananaBlaster::update() {
    position.x += speed;
    // Inactivates lasers given y_coords
    if (active) {
        // Deactivate if the laser has traveled more than a certain distance
        // from fire_pos
        const int max_distance = 500;
        if (std::abs(position.x - fire_pos) > max_distance) {
            active = false;
        }
    }
}