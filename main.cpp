#include <iostream>
#include "CharacterTypes.h"
#include "Entity.h"
#include "GameUI.h"
using namespace std;

int main() {

    InitWindow(1280, 720, "Dungeons of Agony");
    SetTargetFPS(60);

    GameUI game;

    game.init();

    CloseWindow();

    return 0;
}
