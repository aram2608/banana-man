#ifndef GAME_HPP
#define GAME_HPP

#include "bman/bman.hpp"
#include "enemies/ants.hpp"
#include "map/map.hpp"
#include <cmath>
#include <random>
#include <raylib.h>
#include <vector>

class Game {
  public:
    Game(int map_size, int width, int height, int cell_size, Vector2 bman_size);
    void draw_world();
    void draw_screen();
    void spawn_bman();
    void init_cam();
    void update();
    void draw_blasters();
    void update_blasters();
    void delete_blaster();
    void resolve_blaster_collisions();
    void resolve_platform_collisions();
    int chunk_lookup();
    void make_ants();
    void draw_ants();
    int map_size;
    int width;
    int height;
    int cell_size;
    Vector2 bman_size;
    Vector2 ant_size;
    BananaMan player;
    Camera2D camera;

  private:
    Map map;
    std::vector<Ants> ants;
};

#endif