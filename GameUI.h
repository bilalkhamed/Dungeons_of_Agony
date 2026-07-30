#ifndef GAMEUI_H
#define GAMEUI_H

#include <iostream>
#include "Player.h"
using namespace std;

class GameUI {
private:
    void clearScreen() const;
    char getCleanInput() const;
public:
    int showMainMenu() const;

    char showDifficultyMenu(int) const;

    char showClassMenu(int) const;

    char drawGrid(const Player&, int, int, int, const bool doorsCleared[], int, string&) const;

    bool CheckInput(const Player&, int, int&, int&, string&, bool&) const;

    void showDungeonEntryScreen() const;
};

#endif //GAMEUI_H