#include "game.hpp"

Game::Game() {
    player = BananaMan();
    platform = Platform();
}

void Game::draw() {
    player.draw();
    platform.draw();
}

void Game::update() {
    player.update();
    check_grounded();
}

void Game::check_grounded() {
    if (CheckCollisionRecs(player.get_rect(), platform.get_rect())) {
        player.pos.y = platform.pos.y - player.size.y;
        player.velocity.y = 0.0f;
        player.grounded = true;
        player.dj = true;
    } else {
        player.grounded = false;
    }
}
