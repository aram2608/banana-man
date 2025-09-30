#include "../bmanlib/game/configs.hpp"
#include "../bmanlib/game/game.hpp"
#include <raylib.h>

using namespace BManConfigs;

int main() {

    // Game window Audio Device //
    // INITIALIZE FIRST BEFORE LOADING GPU RESOURCES //
    InitWindow(WINDOW_WIDTH, WINDOW_WIDTH, "C++ - Banana Man");

    // Target FPS of 60
    SetTargetFPS(60);
    Game game(MAP_SIZE, WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE, BANANA_SIZE);

    // Game loop. Runs will the window is not closed
    while (!WindowShouldClose()) {

        // Update game events
        game.update();

        // Main logic for drawing to game window
        BeginDrawing();
        ClearBackground({0, 0, 128, 255});
        // We draw our screen in the camera
        game.draw_screen();
        EndDrawing();
    }
    // Close our game window
    CloseWindow();
    return 0;
}