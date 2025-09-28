#include "game.hpp"

Game::Game(int map_size, int width, int height, int cell_size, Vector2 bman_size)
    : map_size(map_size) ,width(width), height(height), cell_size(cell_size), bman_size(bman_size),
      player(bman_size), map(map_size ,width, height, 25, player.size.y) {
    init_cam();
    ant_size = Vector2{30, 30};
    map.create_map();
    spawn_bman();
    //make_ants();
}

// Draw items to screen
void Game::draw_world() {
    player.draw();
    map.draw();
    //draw_ants();
    draw_blasters();
}

void Game::draw_screen() {
    BeginMode2D(camera);
    draw_world();
    EndMode2D();
}

// Function to spawn the banana man
void Game::spawn_bman() {
    // Get get the first platforms rectangle
    Rectangle first_platform = map.map[0][0].get_rect();
    // We then spawn the play slightly to the right of the first platform
    // and we subtract the players heigh to make sure we spawn on top
    player.pos =
        Vector2{first_platform.x + 20, first_platform.y - player.size.y};
}

// We initialize our camera at the start of the game
void Game::init_cam() {
    /*
     * We zero initialize the camera so each member is set to 0
     * We use a double {{}} here to get the compiler to stop complaining
     * A single {} is C compliant but the C++ tends to be a bit stricter
     * w/warnings enabled
     */
    camera = {{0}};
    camera.target = Vector2{player.size.x + 20.0f, player.size.y + 20.0f};
    camera.offset = Vector2{width / 2.0f, height / 2.0f};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
}

// Method to update game state
void Game::update() {
    player.update();
    // We need to snap our position to an int back to a float to remove camera
    // jitter
    camera.target = Vector2{(float)(int)player.pos.x, (float)(int)player.pos.y};
    resolve_blaster_collisions();
    resolve_platform_collisions();
    update_blasters();
    delete_blaster();
    if (ants.size() == 0) {
        make_ants();
    }
}

void Game::draw_blasters() {
    // Iterate over vector of blasters and draw
    for (auto &blaster : player.blasters) {
        blaster.draw();
    }
}

void Game::update_blasters() {
    // Iterate over vector of blasters and update positions
    for (auto &blaster : player.blasters) {
        blaster.update();
    }
}

// Function to delete blasters to protect memory resources
void Game::delete_blaster() {
    // Iterator to loop through the vector and remove any inactive blasters
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

// Function to catch blaster collisions
void Game::resolve_blaster_collisions() {
    // We need to iterate over both the ants and the blasters to catch
    // collisions
    for (auto ant = ants.begin(); ant != ants.end();) {
        bool ant_hit = false;
        for (auto blaster = player.blasters.begin();
             blaster != player.blasters.end();) {
            if (CheckCollisionRecs(ant->get_rect(), blaster->get_rect())) {
                // We erase the blaster and update the iterator
                blaster = player.blasters.erase(blaster);
                // We can then mark the ant for removal
                ant_hit = true;
            } else {
                ++blaster;
            }
        }
        // We can now remove the ant if it is marked
        if (ant_hit) {
            ant = ants.erase(ant);
        } else {
            ++ant;
        }
    }
}

// Function to resolve platform collisions
void Game::resolve_platform_collisions() {
    // We start off by assuming the player is not grounded
    player.grounded = false;

    // We iterate over each grid in the map and resolve the collisions for the 
    // underlying platforms, yes this is very inefficent
    for (auto& grid: map.map) {
        // We iterate through all the platforms in the grid
        for (auto &plat : grid) {
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
}

void Game::make_ants() {
    // We create a random device to seed our Merssene Twister object
    std::random_device rd;
    std::mt19937 gen(rd());
    // Every number within the specified range has an equal
    // probability of being generated
    // 0 is our lower bound and 1 is our upper bound
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    // Minimum distance from player
    const float min_distance = 200.0f;
    
    for (auto& grid: map.map) {
    // We iterate over the platforms
        for (auto &plat : grid) {
            // 30% chance to spawn an ant on this platform
            if (chance(gen) < 0.3f) {
                Rectangle plat_rect = plat.get_rect();
                // We pick a random x position on the platform
                std::uniform_real_distribution<float> x_dist(
                    plat_rect.x, plat_rect.x + plat_rect.width - ant_size.x);

                // We set the x distance to a randomly generated value found in the
                // platform
                Vector2 ant_pos = {x_dist(gen), plat_rect.y - ant_size.y};

                // We calculate the number of pixels between the ant and the player
                // in both the x and y coords
                float dx = ant_pos.x - player.pos.x;
                float dy = ant_pos.y - player.pos.y;
                // We can then check the distance by finding the square root of the
                // calculated dx and dy squared
                float dist = std::sqrt((dx * dx) + (dy * dy));

                // If the ant is far away enough we can create it
                if (dist >= min_distance) {
                    ants.emplace_back(ant_pos, ant_size);
                }
            }
        }
    }
}

// Small helper to draw ants
void Game::draw_ants() {
    for (auto &ant : ants) {
        ant.draw();
    }
}
