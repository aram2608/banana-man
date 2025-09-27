#include "bman/bman.hpp"

BananaMan::BananaMan() {
    pos = Vector2{100, 100};
    size = Vector2{30, 30};
    velocity = Vector2{0, 0};
    gravity = 900.0f;
    grounded = false;
    speed = 200.0f;

    coyote = 0.0f;
    jump_buffer = 0.0f;
    jump_velocity = -350.0f;
    can_double = false;
    restitution = 0.0f;
}

void BananaMan::draw() {
    // For now we are using a simple rectangle
    DrawRectangle((int)pos.x, (int)pos.y, (int)size.x, (int)size.y,
                  {255, 225, 53, 255});
}

void BananaMan::update() {
    float dt = GetFrameTime();
    prev_pos = pos;

    // Handle keyboard inputs
    keyboard(dt);

    // Collisions will zero velocity.y and set grounded
    velocity.y += gravity * dt;

    // Integrate
    pos.x += velocity.x * dt;
    pos.y += velocity.y * dt;

    // Timers tick down each frame, 100 ms of coyote time
    coyote = grounded ? 0.10f : std::max(0.0f, coyote - dt);
    // We calculate our jump_buffer from the greater of the two given values
    jump_buffer = std::max(0.0f, jump_buffer - dt);
}

void BananaMan::keyboard(float dt) {
    // Horizontal
    velocity.x = 0.0f;
    if (IsKeyDown(KEY_LEFT)) {
        velocity.x -= speed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        velocity.x += speed;
    }

    // Double jump, we make sure we are not grounded and are allowed to double
    if (IsKeyPressed(KEY_UP) && !grounded && can_double) {
        velocity.y = jump_velocity;
        can_double = false;
    }

    // Jump up
    if (IsKeyPressed(KEY_UP)) {
        // Set jump_buffer for 120 ms
        jump_buffer = 0.12f;
    }

    // Use the buffered jump if allowed
    if (jump_buffer > 0.0f && (grounded || coyote > 0.0f)) {
        velocity.y = jump_velocity;
        grounded = false;
        coyote = 0.0f;
        jump_buffer = 0.0f;
        can_double = true;
    }
}

Rectangle BananaMan::get_rect() { return {pos.x, pos.y, size.x, size.y}; }

Rectangle BananaMan::get_prev_rect() {
    return {prev_pos.x, prev_pos.y, size.x, size.y};
}