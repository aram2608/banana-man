#include "bman/bman.hpp"
#include "bman.hpp"

BananaMan::BananaMan(Vector2 size) : size(size) {
    // Ground movement
    velocity = Vector2{0, 0};
    max_speed = 200.0f;
    accel_ground = 1800.0f;
    decel_ground = 2000.0f;

    // Jumping
    grounded = false;
    gravity = 900.0f;
    coyote = 0.0f;
    jump_buffer = 0.0f;
    jump_velocity = -350.0f;
    can_double = false;
    restitution = 0.0f;

    // Slidig mechanic
    slide_cooldown = 0.35f;
    slide_duration = 0.25f;
    sliding = false;
    slide_timer = 0.0f;
    can_slide = true;
    slide_speed = 800.0f;
    slide_friction = 2800.0f;
    slide_cd_left = 0.0f;
}

void BananaMan::draw() {
    // For now we are using a simple rectangle
    DrawRectangle((int)pos.x, (int)pos.y, (int)size.x, (int)size.y,
                  {255, 225, 53, 255});
}

void BananaMan::update() {
    float dt = GetFrameTime();
    prev_pos = pos;

    // Timers
    // Coyotoe timer
    coyote = grounded ? 0.10f : std::max(0.0f, coyote - dt);
    // Jump buffer
    jump_buffer = std::max(0.0f, jump_buffer - dt);
    // Slide timer
    slide_cd_left = std::max(0.0f, slide_cd_left - dt);

    // Handle keyboard inputs
    keyboard(dt);

    // Collisions will zero velocity.y and set grounded
    // Gravity is always applied to bman
    velocity.y += gravity * dt;

    // Integrate keyboard changes to position
    pos.x += velocity.x * dt;
    pos.y += velocity.y * dt;
}

void BananaMan::keyboard(float dt) {
    // Helper method to apply gravity and friction
    auto approach = [&](float v, float target, float amount) {
        if (v < target) {
            // If velocity is less than our target we return the smaller
            // of the amount plus our velocity and the target
            return std::min(v + amount, target);
        }
        if (v > target) {
            return std::max(v - amount, target);
        }
        return v;
    };

    // We use the keys to pick the direction of movement
    int dir = 0;
    if (IsKeyDown(KEY_LEFT)) {
        dir -= 1;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        dir += 1;
    }

    // Start slide:
    // press S key + a direction while not on not on cooldown
    // can air glide
    if (!sliding && slide_cd_left <= 0.0f && IsKeyPressed(KEY_S) && dir != 0 &&
        can_slide) {
        sliding = true;
        slide_timer = slide_duration;
        slide_cd_left = slide_cooldown;
        // impulse
        velocity.x = (float)dir * slide_speed;
    }

    if (sliding) {
        // We set our timer to the games time frame
        slide_timer -= dt;

        // Friction fights horizontal velocity toward 0
        velocity.x = approach(velocity.x, 0.0f, slide_friction * dt);

        // We keep a minimum for a snappier feel
        if (fabsf(velocity.x) < 40.0f) {
            velocity.x = 0.0f;
        }

        // If our slide timer is less than or equal to 0
        // or the absolute value of our velocity is less than or equal to 1
        // we set our slide to false
        if (slide_timer <= 0.0f || fabsf(velocity.x) <= 1.0f) {
            sliding = false;
        }
        // We ignore run input while sliding
    } else {
        // FOr ground control we use simple acceleration vs decel movement
        if (dir != 0) {
            velocity.x =
                /*
                 * Our target is the direction times max speed,
                 * and amount is the ground acceleration * the game's frame time
                 */
                approach(velocity.x, (float)dir * max_speed, accel_ground * dt);
        } else {
            /*
             * Our target is 0 since we want to go back to stationary position
             * we set the amount to the deceleration for ground movement *
             * the games' frame time
             */
            velocity.x = approach(velocity.x, 0.0f, decel_ground * dt);
        }
    }

    // Jump buffering / coyote logic for jumps
    if (IsKeyPressed(KEY_UP) && !grounded && can_double) {
        velocity.y = jump_velocity;
        can_double = false;
    } else if (IsKeyPressed(KEY_UP)) {
        jump_buffer = 0.12f;
    }

    // Buffered jumps
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