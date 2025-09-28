#include "map.hpp"

Map::Map(int map_size, int width, int height, int cell_size, int banana_height)
    : map_size(map_size), grids(width, height, cell_size, banana_height) {
}

void Map::create_map() {
    for (int i = 0; i <= map_size; ++i) {
        map.push_back(grids.create_grid(map_size));
    }
}

void Map::draw() {
    for (auto& grid: map) {
        for(auto& p: grid) {
            p.draw();
        }
    }
}