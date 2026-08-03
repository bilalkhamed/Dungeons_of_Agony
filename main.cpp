#include "raylib.h"
#include "Game.h"

int main() {
    InitWindow(1280, 720, "Dungeons of Agony");
    SetTargetFPS(60);

    Game game;
    game.run();

    CloseWindow();
    return 0;
}
