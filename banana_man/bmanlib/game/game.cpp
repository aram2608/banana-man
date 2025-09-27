#include "game.hpp"

std::vector<std::string> level = {
    "............................", "............................",
    "...........###..............", ".........#####..............",
    "############################"};

Game::Game() : grid(800, 800, 25) {
    player = BananaMan();
    grid.create_map(level);
}

void Game::draw() {
    player.draw();
    grid.draw();
}

void Game::update() {
    player.update();
    check_grounded();
}

void Game::check_grounded() {
    player.grounded = false;
    Rectangle pr = player.get_rect();

    for (auto const& plat : grid.platforms) {
        Rectangle tr = plat.get_rect();
        if (CheckCollisionRecs(pr, tr)) {
            player.pos.y = plat.pos.y - player.size.y;
            player.velocity.y = 0.0f;
            player.grounded = true;
            player.dj = true;
            pr.y = player.pos.y;
        }
    }
}