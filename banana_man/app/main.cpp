#include "../bmanlib/game/game.hpp"
#include <raylib.h>

int main() {
    // Hard coded window values
    const int window_w = 800;
    const int window_h = 800;

    // Game window Audio Device //
    // INITIALIZE FIRST BEFORE LOADING GPU RESOURCES //
    InitWindow(window_w, window_h, "C++ - Banana Man");
    InitAudioDevice();

    // Target FPS of 60
    SetTargetFPS(60);
    Game game;

    // Game loop. Runs will the window is not closed
    while (!WindowShouldClose()) {

        // Update game events
        game.update();

        // Main logic for drawing to game window
        BeginDrawing();
        ClearBackground({0, 0, 128, 255});
        game.draw();

        EndDrawing();
    }
    // Close our game window
    CloseWindow();
    CloseAudioDevice();
    return 0;
}