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
    void check_grounded();

  private:
    BananaMan player;
    Grid grid;
};

#endif