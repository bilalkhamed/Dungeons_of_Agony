#ifndef GAMEUI_H
#define GAMEUI_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Entity.h"
#include "raylib.h"
using namespace std;

class Dungeon {
public:
    int id;
    int x;
    int y;
    bool isUnlocked;
    bool isCleared;
    Entity* Boss;
};

class GameUI {
private:
    // Data Members
    Texture2D texture;
    float timer = 0.0f;
    string logs[4];
    int logCount = 0;
public:
    // Constructor & Destructor
    GameUI();
    ~GameUI();

    void init(const char* imagePath);
    void unload();
    void updateTimer();
    void addLog(const string& text);
    void clearLogs();

    static bool IsHovered(Rectangle rect);
    static bool IsClicked(Rectangle rect);

    // Drawing functions
    void drawBackground(int width, int height);
    void drawLoadingScreen(int width);
    void drawPressStart(int width);
    void drawMainMenu();
    void drawHowToPlay();
    void drawNameEntry(const string& text);
    void drawDifficultySelection();
    void drawClassSelection();

    void drawMapScreen(Player* p, const string& name, const string& className, int maxHp, Dungeon map[], int totalDungeons, int selectedInDungeon, bool isInCombat, int EnemyMaxHp);

    void drawShopScreen(Player* p);
    void drawGameOverScreen();
};

#endif