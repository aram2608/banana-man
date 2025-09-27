#include "bman/bman.hpp"
#include "bman.hpp"

BananaMan::BananaMan() {
    pos = Vector2{100, 100};
    size = Vector2{30, 30};
    velocity = Vector2{0, 0};
    gravity = 900.0f;
    grounded = false;
    speed = 200.0f;
    dj = false;
}

void BananaMan::draw() {
    // For now we are using a simple rectangle
    DrawRectangle(pos.x, pos.y, size.x, size.y, {255, 225, 53, 255});
}

void BananaMan::update() {
    // We check if the player is grounded
    if (!grounded) {
        // If not we get the frame time and apply it to our velocity
        float dt = GetFrameTime();
        velocity.y += gravity * dt;
        pos.y += velocity.y * dt;
    }
    keyboard();
}

void BananaMan::keyboard() {
    float dt = GetFrameTime();
    if (IsKeyDown(KEY_LEFT)) {
        pos.x -= speed * dt;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        pos.x += speed * dt;
    }
    if (IsKeyDown(KEY_UP) && grounded) {
        velocity.y = -350.0f;
        grounded = false;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        if (dj) {
            double_jump();
        }
    }
}

Rectangle BananaMan::get_rect() { return {pos.x, pos.y, size.x, size.y}; }

void BananaMan::double_jump() {
    velocity.y = -350.0f;
    dj = false;
}
