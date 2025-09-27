#include "platforms/grid.hpp"
#include "grid.hpp"

Grid::Grid(int width, int height, int cell_size)
    // We calculate the total rows and cols by dividing the height and width by
    // cell_size
    : rows(height / cell_size), cols(width / cell_size), cell_size(cell_size) {}

// Function to create a grid of the map
void Grid::create_map(const std::vector<std::string> &layout) {
    // Pre-reserve approximate number of platforms for performance
    platforms.reserve(rows * cols / 4);

    // We iterate over the grid based on the size of the screen
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (r < (int)layout.size() && c < (int)layout[r].size() &&
                layout[r][c] == '#') {
                // We calculate the position by multiplying the column and row positions
                // by the cell size
                Vector2 pos = {(float)(c * cell_size), (float)(r * cell_size)};
                // We store the size as a vector of the cell sizes
                Vector2 size = {(float)cell_size, (float)cell_size};
                platforms.emplace_back(pos, size);
            }
        }
    }
}

// Function to iterate over each platform and draw it
void Grid::draw() {
    for (auto const &p : platforms) {
        p.draw();
    }
}