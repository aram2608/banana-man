#ifndef GAME_HPP
#define GAME_HPP

#include "bman/bman.hpp"
#include "platforms/grid.hpp"
#include "platforms/platform.hpp"
#include <raylib.h>

class Game {
  public:
    Game();
    void draw();
    void update();
    void resolve_platform_collisions();

  private:
    BananaMan player;
    Grid grid;
};

#endif