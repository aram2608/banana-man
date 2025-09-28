#ifndef GAME_HPP
#define GAME_HPP

#include "bman/bman.hpp"
#include "enemies/ants.hpp"
#include "platforms/grid.hpp"
#include "platforms/platform.hpp"
#include <cmath>
#include <random>
#include <raylib.h>
#include <vector>

class Game {
  public:
    Game(int width, int height, int cell_size, Vector2 bman_size);
    void draw();
    void spawn_bman();
    void update();
    void draw_blasters();
    void update_blasters();
    void delete_blaster();
    void resolve_blaster_collisions();
    void resolve_platform_collisions();
    void make_ants();
    void draw_ants();
    int width;
    int height;
    int cell_size;
    Vector2 bman_size;
    Vector2 ant_size;
    BananaMan player;

  private:
    Grid grid;
    std::vector<Ants> ants;
};

#endif