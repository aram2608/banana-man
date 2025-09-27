#ifndef BMAN_HPP
#define BMAN_HPP

#include "bman/banana_blaster.hpp"
#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <vector>

struct BananaMan {
    BananaMan(Vector2 size);
    void draw();
    void update();
    void keyboard(float dt);
    Rectangle get_rect();
    Rectangle get_prev_rect();
    void fire_laser(int dir);
    double fire_time;
    bool grounded;
    bool can_double;
    bool can_slide;
    bool sliding;
    Vector2 pos;
    Vector2 prev_pos;
    Vector2 size;
    Vector2 velocity;
    int prev_dir;
    float slide_cooldown;
    float slide_duration;
    float slide_cd_left;
    float slide_friction;
    float slide_timer;
    float accel_ground;
    float decel_ground;
    float gravity;
    float max_speed;
    float restitution;
    float jump_velocity;
    float slide_speed;
    float jump_buffer;
    float coyote;

    // Bananablaster
    std::vector<BananaBlaster> blasters;
};

#endif