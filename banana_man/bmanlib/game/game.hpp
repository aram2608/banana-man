#ifndef GAME_HPP
#define GAME_HPP

#include "bman/bman.hpp"
#include "platforms/grid.hpp"
#include "platforms/platform.hpp"
#include <raylib.h>

class Game {
  public:
    Game(int width, int height, int cell_size, Vector2 bman_size);
    void draw();
    void update();
    void resolve_platform_collisions();
    int width;
    int height;
    int cell_size;
    Vector2 bman_size;

  private:
    BananaMan player;
    Grid grid;
};

#endif