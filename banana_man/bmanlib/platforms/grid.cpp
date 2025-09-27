#include "platforms/grid.hpp"
#include "grid.hpp"

Grid::Grid(int width, int height, int cell_size)
    // We calculate the total rows and cols by dividing the height and width by
    // cell_size
    : rows(height / cell_size), cols(width / cell_size), cell_size(cell_size) {}

// Function to create a grid of the map
void Grid::create_map() {
    std::vector<std::vector<int>> layout = generate_random_level(rows, cols);
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

// Function to iterate over each platform and draw it
void Grid::draw() {
    for (auto const &p : platforms) {
        p.draw();
    }
}

// Function to generate random levels
std::vector<std::vector<int>> Grid::generate_random_level(int rows, int cols) {
    int maxGap = 2;
    int maxRise = 1;
    int maxDrop = 2;
    int minRun = 3;
    int maxRun = 7;
    bool solidFloor = true;
    // We create a seed using the current time
    unsigned seed = (unsigned)std::time(nullptr);
    // We create a vector of vectors to represent our level
    std::vector<std::vector<int>> lvl(rows, std::vector<int>(cols, 0));

    // We create our random number generator from our seed
    std::mt19937 rng(seed);

    auto pick = [&](int a, int b) {
        std::uniform_int_distribution<int> d(a, b);
        return d(rng);
    };

    // Helper to place a horizontal run at y across [x0, x1] inclusive
    auto place_run = [&](int y, int x0, int x1) {
        x0 = std::max(0, x0);
        x1 = std::min(cols - 1, x1);
        if (y < 0 || y >= rows)
            return;
        for (int x = x0; x <= x1; ++x)
            lvl[y][x] = 1;
    };

    // Start near the bottom
    int y = rows - 3; // playable lane (leave 1 row above ground)
    int x = 1;

    // Optional base floor
    if (solidFloor) {
        for (int c = 0; c < cols; ++c)
            lvl[rows - 1][c] = 1;
    }

    // Build the main path across the level
    while (x < cols - 2) {
        // 1) Flat segment
        int run = pick(minRun, maxRun);
        place_run(y, x, std::min(x + run - 1, cols - 2));
        x += run;

        if (x >= cols - 2)
            break;

        // 2) Pick a transition: gap, step up, or step down (biased toward
        // flat/gap)
        enum Action { GAP, STEP_UP, STEP_DOWN };
        Action a;
        int r = pick(0, 9);
        if (r < 5)
            a = GAP; // 50%
        else if (r < 7)
            a = STEP_UP; // 20%
        else
            a = STEP_DOWN; // 30%

        if (a == GAP) {
            int gap = pick(1, maxGap);
            // leave 'gap' empty tiles
            x += gap;
            // small safety: add a single landing pillar if we’re near edges
            if (x < cols - 2) {
                // nothing to do; next loop lays the landing run
            }
        } else if (a == STEP_UP) {
            int rise = pick(1, maxRise);
            y = std::max(1, y - rise); // move lane up
            // Add a "stair" pillar under the step to make it look intentional
            // (optional)
            lvl[y][x] = 1;
        } else { // STEP_DOWN
            int drop = pick(1, maxDrop);
            y = std::min(rows - 3, y + drop); // move lane down
            // Optionally add a small filler after drops to avoid awkward gaps
            lvl[y][x] = 1;
        }
    }

    // 3) Decorate (optional): sprinkle short side platforms above/below the
    // path
    std::uniform_int_distribution<int> chance(0, 99);
    for (int c = 2; c < cols - 2; ++c) {
        for (int r2 = 1; r2 < rows - 2; ++r2) {
            if (lvl[r2][c] == 1 && chance(rng) < 12) {
                // Add a tiny ledge above or below
                int dy = (chance(rng) < 50) ? -2 : +2;
                int y2 = std::clamp(r2 + dy, 1, rows - 3);
                int len = pick(2, 4);
                place_run(y2, c, std::min(c + len, cols - 2));
            }
        }
    }
    return lvl;
}