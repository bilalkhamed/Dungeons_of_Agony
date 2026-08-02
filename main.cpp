#include "raylib.h"
#include "GameUI.h"
#include "Dungeon.h"
#include "Player.h"
#include "CharacterTypes.h"
#include "Items/Potion.h"
#include <iostream>
#include <string>

using namespace std;

enum State { MENU, HOW_TO, NAME_ENTRY, DIFFICULTY, CLASS, MAP, SHOP, GAME_OVER };

int main() {
    InitWindow(1280, 720, "Dungeons of Agony");
    SetTargetFPS(60);

    GameUI ui;
    ui.init();

    State state = MENU;
    string heroName = "";
    string heroClass = "Warrior";

    int maxHp = 150;
    int selectedDungeon = 0;
    int totalDungeons = 3;

    Player* player = nullptr;
    Dungeon map[10];

    // Armor locks to prevent stacking
    bool ownsChainArmor = false;
    bool ownsIronArmor = false;
    bool ownsDiamondArmor = false;
    bool ownsDragonArmor = false;

    while (!WindowShouldClose()) {
        ui.updateTimer();

        switch (state) {
            case MENU:
                if (IsKeyPressed(KEY_ONE) || GameUI::IsClicked({ 460, 355, 360, 45 })) {
                    state = NAME_ENTRY;
                }
                if (IsKeyPressed(KEY_TWO) || GameUI::IsClicked({ 460, 425, 360, 45 })) {
                    state = HOW_TO;
                }
                if (IsKeyPressed(KEY_THREE) || GameUI::IsClicked({ 460, 495, 360, 45 })) {
                    goto exit_game;
                }
                break;

            case HOW_TO:
                if (IsKeyPressed(KEY_BACKSPACE) || GameUI::IsClicked({ 420, 600, 380, 30 })) {
                    state = MENU;
                }
                break;

            case NAME_ENTRY: {
                int ch = GetCharPressed();
                while (ch > 0) {
                    if (ch >= 32 && ch <= 125 && heroName.length() < 12) {
                        heroName += (char)ch;
                    }
                    ch = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE) && !heroName.empty()) {
                    heroName.pop_back();
                }
                if ((IsKeyPressed(KEY_ENTER) || GameUI::IsClicked({ 460, 460, 360, 40 })) && !heroName.empty()) {
                    state = DIFFICULTY;
                }
                break;
            }

            case DIFFICULTY: {
                int countChoice = 0;
                if (IsKeyPressed(KEY_ONE)   || GameUI::IsClicked({ 440, 270, 400, 50 })) countChoice = 3;
                if (IsKeyPressed(KEY_TWO)   || GameUI::IsClicked({ 440, 340, 400, 50 })) countChoice = 6;
                if (IsKeyPressed(KEY_THREE) || GameUI::IsClicked({ 440, 410, 400, 50 })) countChoice = 10;

                if (countChoice > 0) {
                    totalDungeons = countChoice;
                    selectedDungeon = 0;

                    for (int i = 0; i < totalDungeons; i++) {
                        map[i].x = 220 + (i * 90);
                        map[i].y = 320 + ((i % 2) * 40);
                        map[i].isUnlocked = (i == 0);
                        map[i].isCleared = false;
                        map[i].boss = Entity(80 + (i * 35), 8 + (i * 3), 1);
                    }
                    state = CLASS;
                }
                break;
            }

            case CLASS: {
                int choice = 0;
                if (IsKeyPressed(KEY_ONE)   || GameUI::IsClicked({ 140, 140, 280, 480 })) choice = 1;
                if (IsKeyPressed(KEY_TWO)   || GameUI::IsClicked({ 500, 140, 280, 480 })) choice = 2;
                if (IsKeyPressed(KEY_THREE) || GameUI::IsClicked({ 860, 140, 280, 480 })) choice = 3;

                if (choice > 0) {
                    delete player;
                    if (choice == 1) { player = new Warrior();  heroClass = "Warrior"; }
                    if (choice == 2) { player = new Mage();     heroClass = "Mage"; }
                    if (choice == 3) { player = new Assassin(); heroClass = "Assassin"; }

                    maxHp = player->getHp();
                    state = MAP;
                }
                break;
            }

            case MAP: {
                if (IsKeyPressed(KEY_RIGHT) && selectedDungeon < totalDungeons - 1 && map[selectedDungeon + 1].isUnlocked) {
                    selectedDungeon++;
                }
                if (IsKeyPressed(KEY_LEFT) && selectedDungeon > 0) {
                    selectedDungeon--;
                }
                if (IsKeyPressed(KEY_S)) {
                    state = SHOP;
                }

                bool doorClicked = false;
                for (int i = 0; i < totalDungeons; i++) {
                    Rectangle doorBox = { (float)map[i].x - 35, (float)map[i].y - 45, 70, 90 };
                    if (GameUI::IsClicked(doorBox)) {
                        selectedDungeon = i;
                        doorClicked = true;
                        break;
                    }
                }

                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_A) || doorClicked) {
                    Dungeon& curr = map[selectedDungeon];

                    if (curr.isCleared) {
                        ui.addLog(TextFormat("Dungeon %d is already cleared!", curr.getId()));
                    } else if (!curr.isUnlocked) {
                        ui.addLog(TextFormat("Dungeon %d is locked!", curr.getId()));
                    } else if (player != nullptr) {
                        bool won = curr.fight(*player);

                        if (won) {
                            curr.isCleared = true;
                            if (selectedDungeon + 1 < totalDungeons) {
                                map[selectedDungeon + 1].isUnlocked = true;
                            }

                            int goldReward = 20 + (selectedDungeon * 15);
                            player->increaseGold(goldReward);
                            ui.addLog(TextFormat("VICTORY! Dungeon %d Cleared! (+%d Gold)", curr.getId(), goldReward));
                        } else {
                            ui.addLog(TextFormat("DEFEAT in Dungeon %d!", curr.getId()));
                            state = GAME_OVER;
                        }
                    }
                }
                break;
            }

            case SHOP: {
                if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_S) || GameUI::IsClicked({ 400, 625, 480, 35 })) {
                    state = MAP;
                }

                if (player != nullptr) {
                    // --- POTIONS (Fully integrated with backend) ---
                    if (GameUI::IsClicked({ 140, 180, 300, 70 })) { // Health Potion
                        Potion p("health");
                        if (player->getGold() >= p.getPrice()) {
                            if (player->addPotion(p)) {
                                player->setGold(player->getGold() - p.getPrice());
                                ui.addLog(TextFormat("Bought Health Potion (-%.0f G)", p.getPrice()));
                            } else {
                                ui.addLog("Inventory is full!");
                            }
                        } else {
                            ui.addLog("Not enough gold!");
                        }
                    }

                    if (GameUI::IsClicked({ 140, 260, 300, 70 })) { // Strength Potion
                        Potion p("strength");
                        if (player->getGold() >= p.getPrice()) {
                            if (player->addPotion(p)) {
                                player->setGold(player->getGold() - p.getPrice());
                                ui.addLog(TextFormat("Bought Strength Potion (-%.0f G)", p.getPrice()));
                            } else {
                                ui.addLog("Inventory is full!");
                            }
                        } else {
                            ui.addLog("Not enough gold!");
                        }
                    }

                    if (GameUI::IsClicked({ 140, 340, 300, 70 })) { // Resistance Potion
                        Potion p("resistance");
                        if (player->getGold() >= p.getPrice()) {
                            if (player->addPotion(p)) {
                                player->setGold(player->getGold() - p.getPrice());
                                ui.addLog(TextFormat("Bought Resistance Potion (-%.0f G)", p.getPrice()));
                            } else {
                                ui.addLog("Inventory is full!");
                            }
                        } else {
                            ui.addLog("Not enough gold!");
                        }
                    }

                    // --- ARMORS (Temporary bypass with locks) ---
                    if (GameUI::IsClicked({ 640, 180, 380, 70 })) { // Chain Armor
                        if (ownsChainArmor) {
                            ui.addLog("You already own Chain Armor!");
                        } else if (player->getGold() >= 10) {
                            player->setGold(player->getGold() - 10);
                            maxHp += 25;
                            player->setHp(player->getHp() + 25);
                            ownsChainArmor = true;
                            ui.addLog("Bought Chain Armor (+25 Max HP | -10 G)");
                        } else {
                            ui.addLog("Not enough gold!");
                        }
                    }

                    if (GameUI::IsClicked({ 640, 260, 380, 70 })) { // Iron Armor
                        if (ownsIronArmor) {
                            ui.addLog("You already own Iron Armor!");
                        } else if (player->getGold() >= 18) {
                            player->setGold(player->getGold() - 18);
                            maxHp += 50;
                            player->setHp(player->getHp() + 50);
                            ownsIronArmor = true;
                            ui.addLog("Bought Iron Armor (+50 Max HP | -18 G)");
                        } else {
                            ui.addLog("Not enough gold!");
                        }
                    }

                    if (GameUI::IsClicked({ 640, 340, 380, 70 })) { // Diamond Armor
                        if (ownsDiamondArmor) {
                            ui.addLog("You already own Diamond Armor!");
                        } else if (player->getGold() >= 30) {
                            player->setGold(player->getGold() - 30);
                            maxHp += 80;
                            player->setHp(player->getHp() + 80);
                            ownsDiamondArmor = true;
                            ui.addLog("Bought Diamond Armor (+80 Max HP | -30 G)");
                        } else {
                            ui.addLog("Not enough gold!");
                        }
                    }

                    if (GameUI::IsClicked({ 640, 420, 380, 70 })) { // Dragon Scale
                        if (ownsDragonArmor) {
                            ui.addLog("You already own Dragon Scale!");
                        } else if (player->getGold() >= 150) {
                            player->setGold(player->getGold() - 150);
                            maxHp += 150;
                            player->setHp(player->getHp() + 150);
                            ownsDragonArmor = true;
                            ui.addLog("Bought Dragon Scale (+150 Max HP | -150 G)");
                        } else {
                            ui.addLog("Not enough gold!");
                        }
                    }
                }
                break;
            }

            case GAME_OVER:
                if (IsKeyPressed(KEY_ONE) || GameUI::IsClicked({ 460, 360, 360, 50 })) {
                    state = MENU;
                    heroName = "";
                    delete player;
                    player = nullptr;
                    ui.clearLogs();

                    // Reset locks on new run
                    ownsChainArmor = false;
                    ownsIronArmor = false;
                    ownsDiamondArmor = false;
                    ownsDragonArmor = false;
                }
                if (IsKeyPressed(KEY_TWO) || GameUI::IsClicked({ 460, 440, 360, 50 })) {
                    goto exit_game;
                }
                break;
        }

        BeginDrawing();
        ui.drawBackground(1280, 720, (state == MAP) ? "DUNGEON" : "MENU");

        switch (state) {
            case MENU:       ui.drawMainMenu(); break;
            case HOW_TO:     ui.drawHowToPlay(); break;
            case NAME_ENTRY: ui.drawNameEntry(heroName); break;
            case DIFFICULTY: ui.drawDifficultySelection(); break;
            case CLASS:      ui.drawClassSelection(); break;
            case MAP:
                if (player) ui.drawMapScreen(player, heroName, heroClass, maxHp, map, totalDungeons, selectedDungeon);
                break;
            case SHOP:
                if (player) ui.drawShopScreen(player);
                break;
            case GAME_OVER:  ui.drawGameOverScreen(); break;
        }

        EndDrawing();
    }

exit_game:
    delete player;
    ui.unload();
    CloseWindow();
    return 0;
}