#include "enemies/antblaster.hpp"

AntBlaster::AntBlaster(Vector2 position, int fire_dir, int speed)
    : position(position), fire_dir(fire_dir), speed(speed) {
    active = true;
}

// Function to draw AntBlasters to screen
void AntBlaster::draw() {
    // Draw a 4x15 green AntBlaster off the position of each instance of
    // AntBlaster
    if (active)
        DrawRectangle(position.x, position.y, 15, 4, Color{199, 44, 0, 255});
}

// Function to get rectangle for AntBlasters
Rectangle AntBlaster::get_rect() {
    Rectangle rect;
    rect.x = position.x, rect.y = position.y, rect.width = 4;
    rect.height = 15;
    return rect;
}

// Function to update AntBlaster position
void AntBlaster::update() {
    position.x += speed;
    // Inactivates lasers given y_coords
    if (active) {
        // Deactivate if the laser has traveled more than a certain distance
        // from fire_pos
        const int max_distance = 500;
        if (std::abs(position.x - fire_dir) > max_distance) {
            active = false;
        }
    }
}