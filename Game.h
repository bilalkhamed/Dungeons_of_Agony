#ifndef OOP_PROJECT_GAME_H
#define OOP_PROJECT_GAME_H

#include <string>
#include "GameUI.h"
#include "Dungeon.h"
#include "Player.h"
using namespace std;

enum State { MENU, HOW_TO, NAME_ENTRY, DIFFICULTY, CLASS, MAP, SHOP, GAME_OVER, WIN };

class Game {
private:
    GameUI ui;
    State state = MENU;
    bool running = true;

    string heroName;
    string heroClass = "Warrior";
    int maxHp = 150;
    int selectedDungeon = 0;
    int totalDungeons = 3;

    Player* player = nullptr;
    Dungeon map[10];

    bool ownsChainArmor = false;
    bool ownsIronArmor = false;
    bool ownsDiamondArmor = false;
    bool ownsDragonArmor = false;

    void update();
    void drawCurrentState();

    void updateMenu();
    void updateHowTo();
    void updateNameEntry();
    void updateDifficulty();
    void updateClass();
    void updateMap();
    void updateShop();
    void updateGameOver();
    void updateWin();

    bool tryPurchasePotion(const string& type, const string& label);
    bool tryPurchaseArmor(const string& material, const string& label, bool& ownedFlag);

    void resetForNewRun();

public:
    Game();
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void run();
};

#endif //OOP_PROJECT_GAME_H