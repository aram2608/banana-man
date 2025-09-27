#include "../bmanlib/game/game.hpp"
#include <raylib.h>

int main() {
    // Hard coded window values w/offest
    const int off_set = 50;
    const int window_w = 750;
    const int window_h = 700;

    // Game window Audio Device //
    // INITIALIZE FIRST BEFORE LOADING GPU RESOURCES //
    InitWindow(window_w + off_set, window_h + (2 * off_set),
               "C++ - Banana Man");
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