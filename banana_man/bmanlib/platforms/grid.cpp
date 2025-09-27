#include "platforms/grid.hpp"
#include "grid.hpp"

Grid::Grid(int width, int height, int cell_size, int banana_height)
    // We calculate the total rows and cols by dividing the height and width by
    // cell_size
    : rows(height / cell_size), cols(width / cell_size), cell_size(cell_size),
      banana_height(banana_height) {}

// Function to create a grid of the map
void Grid::create_map() {
    std::vector<std::vector<int>> layout = test_map();
    // Pre-reserve approximate number of platforms for performance
    platforms.reserve(rows * cols / 4);

    // We iterate over the grid based on the size of the screen
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (r < (int)layout.size() && c < (int)layout[r].size() &&
                layout[r][c] == 1) {
                // We calculate the position by multiplying the column and row
                // positions by the cell size
                Vector2 pos = {(float)(c * cell_size), (float)(r * cell_size)};
                // We store the size as a vector of the cell sizes
                Vector2 size = {(float)cell_size, (float)cell_size};
                platforms.emplace_back(pos, size);
            }
        }
    }
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

// Function to generate random levels
std::vector<std::vector<int>> Grid::generate_random_level(int rows, int cols) {
    int minRun = 3;
    int maxRun = 7;
    int minGap = 3;
    int maxGap = 6;
    int maxRise = 2;
    int maxDrop = 2;
    int bands = 5;
    int stepEveryCols = 6;
    float jumpVel = -350.0f;
    float gravity = 900.0f;

    unsigned seed = (unsigned)std::time(nullptr);
    std::vector<std::vector<int>> lvl(rows, std::vector<int>(cols, 0));
    std::mt19937 rng(seed);

    auto pick = [&](int a, int b) {
        std::uniform_int_distribution<int> d(a, b);
        return d(rng);
    };

    // top clearance from physics: h = v^2 / (2g)
    float maxJumpPx = (jumpVel * jumpVel) / (2.0f * gravity);
    int topClearRows =
        std::max(1, (int)std::ceil((banana_height + maxJumpPx) / cell_size));
    int yMin = topClearRows; // never place above this
    int yMax = rows - 2;     // keep a pixel row margin above bottom

    auto place_run = [&](int y, int x0, int x1) {
        x0 = std::max(0, x0);
        x1 = std::min(cols - 1, x1);
        if (y < 0 || y >= rows)
            return;
        for (int x = x0; x <= x1; ++x)
            lvl[y][x] = 1;
    };
    auto place_ladder = [&](int x, int yTop, int yBot) {
        yTop = std::max(0, yTop);
        yBot = std::min(rows - 1, yBot);
        for (int y = yTop; y <= yBot; ++y)
            lvl[y][x] = 2;
    };

    // Start from near bottom, respect clearance
    int curY = std::clamp(rows - 3, yMin, yMax);
    int startX = 1; // first band goes left→right
    bool leftToRight = true;

    for (int b = 0; b < bands; ++b) {
        int x = leftToRight ? startX : cols - 2;
        int xEnd = leftToRight ? (cols - 2) : 1;
        int dir = leftToRight ? +1 : -1;

        int stepCounter = 0;
        int y = curY;

        // draw a sloped band with occasional gaps
        while ((leftToRight && x <= xEnd) || (!leftToRight && x >= xEnd)) {
            // optional gap
            if (pick(0, 99) < 18) { // ~18% chance to insert a gap
                int gap = pick(minGap, maxGap);
                x += dir * gap;
                stepCounter += gap;
                // keep bounds
                if (leftToRight) {
                    if (x > xEnd)
                        break;
                } else {
                    if (x < xEnd)
                        break;
                }
            } else {
                // place a short flat run (2–4 tiles) at current y
                int run = pick(2, 4);
                for (int i = 0; i < run; ++i) {
                    if (x < 1 || x > cols - 2)
                        break;
                    if (y < yMin)
                        y = yMin;
                    if (y > yMax)
                        y = yMax;
                    lvl[y][x] = 1;
                    x += dir;
                    stepCounter++;
                }
            }

            // step slope up every N columns
            if (stepCounter >= stepEveryCols) {
                stepCounter = 0;
                y = std::max(yMin, y - 1); // slope upwards one tile
            }
        }

        // end-of-band position (last valid x within bounds)
        int endX = std::clamp(x - dir, 1, cols - 2);
        int endY = y;

        // place a ladder up to next band (guarantee ascent)
        int nextY = std::max(yMin, endY - 3); // climb ~3 rows (tweakable)
        place_ladder(endX, nextY, endY);

        // next band starts from opposite side, a bit higher
        curY = std::max(yMin, endY - 3);
        leftToRight = !leftToRight;
        startX = leftToRight ? 1 : cols - 2;
    }

    // Optional: a small goal platform near the top center
    int goalY = std::max(yMin, curY - 2);
    place_run(goalY, cols / 2 - 3, cols / 2 + 3);

    return lvl;
}