#include "GameUI.h"

enum State { MENU, HOW_TO, NAME_ENTRY, DIFFICULTY, CLASS, MAP, SHOP, GAME_OVER };

int main() {
    InitWindow(1280, 720, "Dungeon Crawler");
    SetTargetFPS(60);



    /* THIS IS A DUMMY MAIN JUST TO TEST THE UI, EDIT LATER */
    GameUI ui;
    ui.init();

    State state = MENU;
    string heroName = "";
    string heroClass = "Warrior";

    int maxHp = 150, enemyMaxHp = 50, selectedDungeon = 0, totalDungeons = 3;
    bool inCombat = false;

    Player player(150, 10, 5, 50.0f);
    Entity boss(50, 10, 2);
    Dungeon map[10];

    auto createMap = [&](int count) {
        totalDungeons = count;
        for (int i = 0; i < count; i++) {
            map[i] = { i + 1, 400 + (i * 80), 300 + ((i % 2) * 40), i == 0, false, &boss };
        }
    };

    while (!WindowShouldClose()) {
        ui.updateTimer();

        switch (state) {
            case MENU:
                if (IsKeyPressed(KEY_ONE)   || ui.IsClicked({460, 290, 360, 45})) state = NAME_ENTRY;
                if (IsKeyPressed(KEY_TWO)   || ui.IsClicked({460, 360, 360, 45})) state = HOW_TO;
                if (IsKeyPressed(KEY_THREE) || ui.IsClicked({460, 430, 360, 45})) goto exit_game;
                break;

            case HOW_TO:
                if (IsKeyPressed(KEY_BACKSPACE) || ui.IsClicked({420, 600, 380, 30})) state = MENU;
                break;

            case NAME_ENTRY: {
                int ch = GetCharPressed();
                while (ch > 0) {
                    if (ch >= 32 && ch <= 125 && heroName.length() < 12) heroName += (char)ch;
                    ch = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE) && !heroName.empty()) heroName.pop_back();
                if ((IsKeyPressed(KEY_ENTER) || ui.IsClicked({460, 460, 360, 40})) && !heroName.empty()) state = DIFFICULTY;
                break;
            }

            case DIFFICULTY: {
                int count = (IsKeyPressed(KEY_ONE)   || ui.IsClicked({440, 270, 400, 50})) ? 3 :
                            (IsKeyPressed(KEY_TWO)   || ui.IsClicked({440, 340, 400, 50})) ? 6 :
                            (IsKeyPressed(KEY_THREE) || ui.IsClicked({440, 410, 400, 50})) ? 10 : 0;
                if (count > 0) { createMap(count); state = CLASS; }
                break;
            }

            case CLASS: {
                int choice = (IsKeyPressed(KEY_ONE)   || ui.IsClicked({140, 200, 280, 400})) ? 1 :
                             (IsKeyPressed(KEY_TWO)   || ui.IsClicked({500, 200, 280, 400})) ? 2 :
                             (IsKeyPressed(KEY_THREE) || ui.IsClicked({860, 200, 280, 400})) ? 3 : 0;
                if (choice) {
                    heroClass = (choice == 1) ? "Warrior" : (choice == 2) ? "Mage" : "Assassin";
                    maxHp     = (choice == 1) ? 150 : (choice == 2) ? 50 : 100;
                    // player.setHp(maxHp);
                    state = MAP;
                }
                break;
            }

            case MAP:
                if (IsKeyPressed(KEY_RIGHT) && selectedDungeon < totalDungeons - 1 && map[selectedDungeon + 1].isUnlocked) selectedDungeon++;
                if (IsKeyPressed(KEY_LEFT)  && selectedDungeon > 0) selectedDungeon--;
                if (IsKeyPressed(KEY_S)) state = SHOP;

                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_A)) {
                    inCombat = true;
                    // boss.setHp(boss.getHp() - player.getDamage());
                    ui.addLog(TextFormat("Dealt %d damage to Boss!", player.getDamage()));
                    if (boss.getHp() <= 0) {
                        map[selectedDungeon].isCleared = true;
                        if (selectedDungeon + 1 < totalDungeons) map[selectedDungeon + 1].isUnlocked = true;
                        inCombat = false;
                        // player.addGold(25);
                        ui.addLog("Victory! +25 Gold earned.");
                    }
                }
                if (player.getHp() <= 0) state = GAME_OVER;
                break;

            case SHOP:
                if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_S) || ui.IsClicked({400, 625, 480, 30})) state = MAP;
                if (ui.IsClicked({140, 180, 300, 70}) && player.getGold() >= 5) {
                    // player.addGold(-5); player.setHp(player.getHp() + 20);
                    ui.addLog("Bought Health Potion (+20 HP)");
                }
                break;

            case GAME_OVER:
                if (IsKeyPressed(KEY_ONE) || ui.IsClicked({460, 360, 360, 50})) { state = MENU; heroName = ""; }
                if (IsKeyPressed(KEY_TWO) || ui.IsClicked({460, 440, 360, 50})) goto exit_game;
                break;
        }

        BeginDrawing();
        ui.drawBackground(1280, 720);

        switch (state) {
            case MENU:       ui.drawMainMenu(); break;
            case HOW_TO:     ui.drawHowToPlay(); break;
            case NAME_ENTRY: ui.drawNameEntry(heroName); break;
            case DIFFICULTY: ui.drawDifficultySelection(); break;
            case CLASS:      ui.drawClassSelection(); break;
            case MAP:        ui.drawMapScreen(&player, heroName, heroClass, maxHp, map, totalDungeons, selectedDungeon, inCombat, enemyMaxHp); break;
            case SHOP:       ui.drawShopScreen(&player); break;
            case GAME_OVER:  ui.drawGameOverScreen(); break;
        }

        EndDrawing();
    }

exit_game:
    CloseWindow();
    return 0;
}