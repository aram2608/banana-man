#include "platforms/grid.hpp"
#include "grid.hpp"

Grid::Grid(int width, int height, int cell_size, int banana_height)
    // We calculate the total rows and cols by dividing the height and width by
    // cell_size
    : width(width), rows(height / cell_size), cols(width / cell_size),
      cell_size(cell_size), banana_height(banana_height) {}

// Function to create a grid of the map
std::vector<Platform> Grid::create_grid(int map_size) {
    std::vector<std::vector<int>> layout = test_map();
    // We iterate over the map size to increase the spacing between platforms
    for (int i = 0; i <= map_size; ++i) {
        // We iterate over the grid based on the size
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (r < (int)layout.size() && c < (int)layout[r].size() &&
                    layout[r][c] == 1) {
                    // We calculate the position by multiplying the column and
                    // row positions by the cell size
                    Vector2 pos = {(float)(c * cell_size) + (width * i),
                                   (float)(r * cell_size)};
                    // We store the size as a vector of the cell sizes
                    Vector2 size = {(float)cell_size, (float)cell_size};
                    platforms.emplace_back(pos, size);
                }
            }
        }
    }
    return platforms;
}

// Function to iterate over each platform and draw it to screen
void Grid::draw() {
    for (auto const &p : platforms) {
        p.draw();
    }
}

std::vector<std::vector<int>> Grid::test_map() {
    // We create a dummy map full of 0s, with one missing row
    std::vector<std::vector<int>> map_1(rows - 1, std::vector<int>(cols, 0));
    // The final row we fill with ones as our floor
    map_1.push_back(std::vector<int>(cols, 1));
    return map_1;
}