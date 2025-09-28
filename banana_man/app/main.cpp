#include "../bmanlib/game/configs.hpp"
#include "../bmanlib/game/game.hpp"
#include <raylib.h>

using namespace BManConfigs;

int main() {

    // Game window Audio Device //
    // INITIALIZE FIRST BEFORE LOADING GPU RESOURCES //
    InitWindow(WINDOW_WIDTH, WINDOW_WIDTH, "C++ - Banana Man");
    InitAudioDevice();

    // Target FPS of 60
    SetTargetFPS(60);
    Game game(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE, BANANA_SIZE);

    Camera2D camera = {0};
    camera.target = (Vector2){BANANA_SIZE.x + 20.0f, BANANA_SIZE.y + 20.0f};
    camera.offset = (Vector2){WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    // Game loop. Runs will the window is not closed
    while (!WindowShouldClose()) {

        // Update game events
        game.update();
        camera.target = game.player.pos;

        // Main logic for drawing to game window
        BeginDrawing();
        ClearBackground({0, 0, 128, 255});
        // We draw our world in the camera
        BeginMode2D(camera);
        game.draw();

        EndMode2D();
        EndDrawing();
    }
    // Close our game window
    CloseWindow();
    CloseAudioDevice();
    return 0;
}