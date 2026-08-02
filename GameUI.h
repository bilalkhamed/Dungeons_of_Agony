#ifndef GAMEUI_H
#define GAMEUI_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Entity.h"
#include "raylib.h"
#include "Dungeon.h"
using namespace std;

class GameUI {
private:
    // Declare all Texture2D members referenced in GameUI.cpp
    Texture2D menuBgTex;
    Texture2D dungeonBgTex;
    Texture2D shopBgTex;
    Texture2D logoTex;
    Texture2D doorTex;
    Texture2D warriorTex;
    Texture2D mageTex;
    Texture2D assassinTex;

    float timer = 0.0f;
    string logs[4];
    int logCount = 0;

public:
    // Constructor & Destructor
    GameUI();
    ~GameUI();

    void init();
    void unload();
    void updateTimer();
    void addLog(const string& text);
    void clearLogs();
    Texture2D loadSafeTexture(const string& filename);

    static bool IsHovered(Rectangle rect);
    static bool IsClicked(Rectangle rect);

    // Drawing functions
    void drawBackground(int width, int height, const string& type);
    void drawLoadingScreen(int width);
    void drawPressStart(int width);
    void drawMainMenu();
    void drawHowToPlay();
    void drawNameEntry(const string& text);
    void drawDifficultySelection();
    void drawClassSelection();

    void drawMapScreen(Player* player, const std::string& name, const std::string& heroClass, int maxHp, Dungeon map[], int totalDungeons, int selectedIndex);

    void drawShopScreen(Player* p);
    void drawGameOverScreen();
};

#endif