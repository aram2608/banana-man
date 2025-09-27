#include "platforms/platform.hpp"
#include "platform.hpp"

Platform::Platform(Vector2 pos, Vector2 size) : pos(pos), size(size) {}

void Platform::draw() const {
    DrawRectangle(pos.x, pos.y, size.x, size.y, {255, 255, 255, 255});
}

Rectangle Platform::get_rect() const { return {pos.x, pos.y, size.x, size.y}; }
