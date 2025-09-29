``` C++
int Simulation::count_neighbors(int r, int c) {
    // An int value to keep track of neighbors
    int live_neighbors = 0;
    // We make a vector of pairs to represent the cells around the cell of
    // interest
    std::vector<std::pair<int, int>> n_offset = {
        {-1, 0},  // Above
        {1, 0},   // Below
        {0, -1},  // Left
        {0, 1},   // Right
        {-1, -1}, // Upper left
        {-1, 1},  // Upper right
        {1, -1},  // Lower left
        {1, 1}    // Lower right
    };
    // We iterate over each offset
    for (const auto &offset : n_offset) {
        // We use modulo arithmetic to create  a toroidal array, meaning the
        // right most edge wraps around and "touches" the leftmost edge so a
        // cell at [5][29] has a neighbor at [5][0]
        int neighbor_row =
            (r + offset.first + grid.rows) % grid.rows;
        int neighbor_col =
            (c + offset.second + grid.cols) % grid.cols;
        // We return the value of at the neighbors location and directly add it
        // to the live neighbor count
        live_neighbors += grid.get_value(neighbor_row, neighbor_col);
    }
    return live_neighbors;
}
```