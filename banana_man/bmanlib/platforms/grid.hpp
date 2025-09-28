#ifndef GRID_HPP
#define GRID_HPP

#include "platforms/platform.hpp"
#include <algorithm>
#include <ctime>
#include <random>
#include <raylib.h>
#include <vector>

class Grid {
  public:
    Grid(int width, int height, int cell_size, int banana_height);
    // Integer representation for the number of rows
    int rows;
    // Integer representation for the number of columns
    int cols;
    // Predefined cell size as an integer
    int cell_size;
    int banana_height;
    int width;
    std::vector<Platform> platforms;
    // Method to create map
    std::vector<Platform> create_grid(int map_size);
    // Method to draw platforms
    void draw();
    std::vector<std::vector<int>> test_map();
    std::vector<std::vector<int>> generate_random_level();

  private:
};

#endif