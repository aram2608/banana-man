#ifndef MAP_HPP
#define MAP_HPP

#include "platforms/grid.hpp"
#include "platforms/platform.hpp"
#include <vector>

struct Map {
    Map(int map_size, int width, int height, int cell_size, int banana_height);
    std::vector<std::vector<Platform>> map;
    void create_map();
    void draw();

    Grid grids;
    int map_size;
    int width;
    int height;
    int cell_size;
    int banana_height;
};

#endif