#include "map/map.hpp"
#include "map/bitmaps.hpp"

Map::Map(int map_size, int width, int height, int cell_size, int banana_height)
    // We calculate the total rows and cols by dividing the height and width by
    // cell_size
    : map_size(map_size), width(width), rows(height / cell_size),
      cols(width / cell_size), cell_size(cell_size),
      banana_height(banana_height) {}

// Function to create a grid of the map
void Map::create_map() {
    std::vector<std::vector<int>> layout = BitMaps::MAP_1;
    // We iterate over the map size to increase the spacing between platforms
    // We iterate over the grid based on the size
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (r < (int)layout.size() && c < (int)layout[r].size() &&
                layout[r][c] == 1) {
                // We calculate the position by multiplying the column and
                // row positions by the cell size
                Vector2 pos = {(float)(c * cell_size), (float)(r * cell_size)};
                // We store the size as a vector of the cell sizes
                Vector2 size = {(float)cell_size, (float)cell_size};
                platforms.emplace_back(pos, size);
            }
        }
    }
}

// Function to iterate over each platform and draw it to screen
void Map::draw() {
    for (auto const &p : platforms) {
        p.draw();
    }
}

std::vector<std::vector<int>> Map::test_map() {
    // We create a dummy map full of 0s, with one missing row
    std::vector<std::vector<int>> map_1(rows - 1, std::vector<int>(cols, 0));
    // The final row we fill with ones as our floor
    map_1.push_back(std::vector<int>(cols, 1));
    return map_1;
}

// Function to generate random levels
std::vector<std::vector<int>> Map::generate_random_level() {
    int min_run = 3;
    int max_run = 7;
    int min_gap = 3;
    int max_gap = 6;
    float jump_vel = -350.0f;
    float gravity = 900.0f;
    float max_jump_px = (jump_vel * jump_vel) / (2.0f * gravity);
    int max_jump_grid = (int)max_jump_px / cell_size;

    // We create a random number generator using the Mersene Twister algorithm
    // and a random device
    std::random_device seed;
    std::mt19937 rng(seed());
    std::vector<std::vector<int>> lvl(rows, std::vector<int>(cols, 0));

    // std::clamp could be useful

    // Helper to gen some high quality random numbers
    auto pick = [&](int a, int b) {
        std::uniform_int_distribution<int> d(a, b);
        return d(rng);
    };

    // Helper to place a run of `length` cells starting at (y, x).
    auto place_run = [&](int y, int x) -> bool {
        // Max cells that can fit starting at x
        int max_len_here = std::min(max_run, cols - x);
        // We check ff the maximum length allowed at our index is less than
        // our predefined minimum run length
        if (max_len_here < min_run) {
            // We return out
            return false;
        }
        // If we pass our test we can generate the run using the minimum run
        // and maximum allowed length
        int length = pick(min_run, max_len_here);
        for (int i = 0; i < length; ++i) {
            lvl[y][x + i] = 1;
        }
        return true;
    };

    // Number of platforms we want drawn
    int max_platforms = 20;

    // Indexes
    int row_end = rows - 1;
    int start = 0;

    // A safety measure so x always allows at least min_run cells
    int max_start_x = std::max(0, cols - min_run);

    // We add a guard to avoid accidental infinite loops
    int safety = 10000;
    // We decrement the number of platforms until we have placed all 20
    while (max_platforms > 0 && safety-- > 0) {
        int row_idx = pick(start, row_end);
        int col_idx = pick(start, max_start_x);
        // We return a bool in our helper to catch out of bounds indices
        if (place_run(row_idx, col_idx)) {
            --max_platforms;
        }
    }
    return lvl;
}

void Map::make_csv(std::vector<std::vector<int>> &lvl) {
    std::ofstream file("map.csv");
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (r < (int)lvl.size() && c < (int)lvl[r].size()) {
                file << lvl[r][c];
                if (c < cols - 1) {
                    file << ",";
                }
            }
        }
        file << "\n";
    }
    file.close();
}
