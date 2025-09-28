#include "enemies/ants.hpp"
#include "ants.hpp"

Ants::Ants(Vector2 pos, Vector2 size) : pos(pos), size(size) {}

void Ants::draw() {
    DrawRectangle(pos.x, pos.y, size.x, size.y, {199, 44, 0, 255});
}

Rectangle Ants::get_rect() { return {pos.x, pos.y, size.x, size.y}; }
