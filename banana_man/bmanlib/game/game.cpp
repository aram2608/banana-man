#include "game.hpp"

Game::Game(int width, int height, int cell_size, Vector2 bman_size)
    : width(width), height(height), cell_size(cell_size), bman_size(bman_size),
      player(bman_size), grid(width, height, 25, player.size.y) {
    grid.create_map();
    spawn_bman();
}

// Draw items to screen
void Game::draw() {
    player.draw();
    grid.draw();
    // Iterate over vector of lasers and draw
    for (auto &laser : player.blasters) {
        laser.draw();
    }
}

// Function to spawn the banana man
void Game::spawn_bman() {
    // Get get the first platforms rectangle
    Rectangle first_platform = grid.platforms[0].get_rect();
    // We then spawn the play slightly to the right of the first platform
    // and we subtract the players heigh to make sure we spawn on top
    player.pos =
        Vector2{first_platform.x + 20, first_platform.y - player.size.y};
}

// Method to update game state
void Game::update() {
    player.update();
    resolve_platform_collisions();
    // Iterate over vector of lasers and update positions
    for (auto &laser : player.blasters) {
        laser.update();
    }
    delete_laser();
}

// Function to delete lasers to protect memory resources
void Game::delete_laser() {
    // Iterator to loop through the vector and remove any inactive ship lasers
    for (auto it = player.blasters.begin(); it != player.blasters.end();) {
        if (!it->active) {
            // Erase returns an iterator pointing to the next item in the vector
            // this keep the iterator going
            it = player.blasters.erase(it);
        } else {
            ++it;
        }
    }
}

// Function to resolve platform collisions
void Game::resolve_platform_collisions() {
    // We start off by assuming the player is not grounded
    player.grounded = false;

    // We iterate through all the platforms in the grid
    for (auto &plat : grid.platforms) {
        // We retireve the player and platform positions
        Rectangle pr = player.get_rect();
        Rectangle tr = plat.get_rect();

        // We check for collisions and continue to the next platform if there
        // are none
        if (!CheckCollisionRecs(pr, tr)) {
            continue;
        }

        // Decide the collision side using our previous position
        Rectangle prev = player.get_prev_rect();

        // Edges (previous frame)
        float prev_left = prev.x;
        float prev_right = prev.x + prev.width;
        float prev_top = prev.y;
        float prev_bottom = prev.y + prev.height;

        // Tile edges
        float t_left = tr.x;
        float t_right = tr.x + tr.width;
        float t_top = tr.y;
        float t_bottom = tr.y + tr.height;

        // We check collisions when the player lands on a tile
        if (prev_bottom <= t_top && player.velocity.y > 0) {
            player.pos.y = t_top - player.size.y;
            player.velocity.y =
                -player.velocity.y * player.restitution; // 0 = stop
            player.grounded = true;
            continue;
        }

        // We check collisions for head bonks
        if (prev_top >= t_bottom && player.velocity.y < 0) {
            player.pos.y = t_bottom;
            player.velocity.y = -player.velocity.y * player.restitution;
            continue;
        }

        // Otherwise it’s a side collision.
        // From left → hit tile’s left side
        if (prev_right <= t_left && player.velocity.x > 0) {
            player.pos.x = t_left - player.size.x;
            player.velocity.x = -player.velocity.x * player.restitution;
            continue;
        }

        // From right → hit tile’s right side
        if (prev_left >= t_right && player.velocity.x < 0) {
            player.pos.x = t_right;
            player.velocity.x = -player.velocity.x * player.restitution;
            continue;
        }
    }
}