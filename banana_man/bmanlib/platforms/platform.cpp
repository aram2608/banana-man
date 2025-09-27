#include "platforms/platform.hpp"
#include "platform.hpp"

Platform::Platform() {
    pos = Vector2{100, 200};
    size = Vector2{400, 30};
}

void Platform::draw() {
    DrawRectangle(pos.x, pos.y, size.x, size.y, {255, 255, 255, 255});
}

Rectangle Platform::get_rect() { return {pos.x, pos.y, size.x, size.y}; }
