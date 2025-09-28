#ifndef MAP_HPP
#define MAP_HPP

#include "platforms/platform.hpp"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <raylib.h>
#include <thread>
#include <vector>

class Map {
  public:
    Map(int map_size, int width, int height, int cell_size, int banana_height);
    // Integer representation for the number of rows
    int rows;
    // Integer representation for the number of columns
    int cols;
    // Predefined cell size as an integer
    int cell_size;
    int banana_height;
    int width;
    int map_size;
    std::vector<Platform> platforms;
    // Method to create map
    void create_map();
    // Method to draw platforms
    void draw();
    std::vector<std::vector<int>> test_map();
    std::vector<std::vector<int>> generate_random_level();

  private:
};

#endif