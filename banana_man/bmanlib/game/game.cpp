#include "game.hpp"

Game::Game(int width, int height, int cell_size, Vector2 bman_size)
    : width(width), height(height), cell_size(cell_size), bman_size(bman_size),
      player(bman_size), grid(width, height, 25, player.size.y) {
    grid.create_map();
    spawn_bman();
}

void Game::draw() {
    player.draw();
    grid.draw();
}

void Game::spawn_bman() {
    // Get get the first platforms rectangle
    Rectangle first_platform = grid.platforms[0].get_rect();
    // We then spawn the play slightly to the right of the first platform
    // and we subtract the players heigh to make sure we spawn on top
    player.pos = Vector2{first_platform.x + 20, first_platform.y - player.size.y};
}

void Game::update() {
    player.update();
    resolve_platform_collisions();
}

void Game::resolve_platform_collisions() {
    player.grounded = false;
    Rectangle pr = player.get_rect();

    for (auto &plat : grid.platforms) {
        Rectangle pr = player.get_rect();
        Rectangle tr = plat.get_rect();

        if (!CheckCollisionRecs(pr, tr))
            continue;

        // Decide the collision side using where we WERE last frame.
        Rectangle prev = player.get_prev_rect();

        // Edges (previous frame)
        float prevLeft = prev.x;
        float prevRight = prev.x + prev.width;
        float prevTop = prev.y;
        float prevBottom = prev.y + prev.height;

        // Tile edges
        float tLeft = tr.x;
        float tRight = tr.x + tr.width;
        float tTop = tr.y;
        float tBottom = tr.y + tr.height;

        // We came from above?
        if (prevBottom <= tTop && player.velocity.y > 0) {
            player.pos.y = tTop - player.size.y; // land on top
            player.velocity.y =
                -player.velocity.y * player.restitution; // 0 = stop
            player.grounded = true;
            continue;
        }

        // We came from below? (head-bonk)
        if (prevTop >= tBottom && player.velocity.y < 0) {
            player.pos.y = tBottom;
            player.velocity.y = -player.velocity.y * player.restitution;
            continue;
        }

        // Otherwise it’s a side collision.
        // From left → hit tile’s left side
        if (prevRight <= tLeft && player.velocity.x > 0) {
            player.pos.x = tLeft - player.size.x;
            player.velocity.x = -player.velocity.x * player.restitution;
            continue;
        }

        // From right → hit tile’s right side
        if (prevLeft >= tRight && player.velocity.x < 0) {
            player.pos.x = tRight;
            player.velocity.x = -player.velocity.x * player.restitution;
            continue;
        }

        // Fallback: if we can’t classify (e.g., starting inside), push out by
        // minimum overlap
        float overlapLeft = (pr.x + pr.width) - tLeft;
        float overlapRight = tRight - pr.x;
        float overlapTop = (pr.y + pr.height) - tTop;
        float overlapBottom = tBottom - pr.y;

        float minH = std::min(overlapLeft, overlapRight);
        float minV = std::min(overlapTop, overlapBottom);

        if (minH < minV) {
            // resolve horizontally
            if (overlapLeft < overlapRight) {
                player.pos.x -= overlapLeft;
            } else {
                player.pos.x += overlapRight;
            }
            player.velocity.x = -player.velocity.x * player.restitution;
        } else {
            // resolve vertically
            if (overlapTop < overlapBottom) {
                player.pos.y -= overlapTop; // push up
                player.grounded = true;
            } else {
                player.pos.y += overlapBottom; // push down
            }
            player.velocity.y = -player.velocity.y * player.restitution;
        }
    }
}