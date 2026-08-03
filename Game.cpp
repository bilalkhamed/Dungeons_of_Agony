#include "Game.h"
#include "CharacterTypes.h"
#include "Items/Armor.h"
#include "raylib.h"

Game::Game() {
    ui.init();
}

Game::~Game() {
    delete player;
    ui.unload();
}

void Game::run() {
    while (running && !WindowShouldClose()) {
        ui.updateTimer();
        update();

        BeginDrawing();
        ui.drawBackground(1280, 720, (state == MAP) ? "DUNGEON" : "MENU");
        drawCurrentState();
        EndDrawing();
    }
}

void Game::update() {
    switch (state) {
        case MENU:       updateMenu(); break;
        case HOW_TO:     updateHowTo(); break;
        case NAME_ENTRY: updateNameEntry(); break;
        case DIFFICULTY: updateDifficulty(); break;
        case CLASS:      updateClass(); break;
        case MAP:        updateMap(); break;
        case SHOP:       updateShop(); break;
        case GAME_OVER:  updateGameOver(); break;
        case WIN:        updateWin(); break;
    }
}

void Game::drawCurrentState() {
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
        case WIN:        ui.drawWinScreen(); break;
    }
}

void Game::updateMenu() {
    if (IsKeyPressed(KEY_ONE) || GameUI::IsClicked({ 460, 355, 360, 45 })) {
        state = NAME_ENTRY;
    }
    if (IsKeyPressed(KEY_TWO) || GameUI::IsClicked({ 460, 425, 360, 45 })) {
        state = HOW_TO;
    }
    if (IsKeyPressed(KEY_THREE) || GameUI::IsClicked({ 460, 495, 360, 45 })) {
        running = false;
    }
}

void Game::updateHowTo() {
    if (IsKeyPressed(KEY_BACKSPACE) || GameUI::IsClicked({ 420, 600, 380, 30 })) {
        state = MENU;
    }
}

void Game::updateNameEntry() {
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
}

void Game::updateDifficulty() {
    int countChoice = 0;
    if (IsKeyPressed(KEY_ONE)   || GameUI::IsClicked({ 440, 270, 400, 50 })) countChoice = 3;
    if (IsKeyPressed(KEY_TWO)   || GameUI::IsClicked({ 440, 340, 400, 50 })) countChoice = 6;
    if (IsKeyPressed(KEY_THREE) || GameUI::IsClicked({ 440, 410, 400, 50 })) countChoice = 10;

    if (countChoice > 0) {
        totalDungeons = countChoice;
        selectedDungeon = 0;

        for (int i = 0; i < totalDungeons; i++) {
            map[i].setPosition(220 + (i * 90), 320 + ((i % 2) * 40));
            map[i].setUnlocked(i == 0);
            map[i].setCleared(false);
            map[i].setBoss(Entity(80 + (i * 35), 8 + (i * 3), 1));
        }
        state = CLASS;
    }
}

void Game::updateClass() {
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
}

void Game::updateMap() {
    if (IsKeyPressed(KEY_RIGHT) && selectedDungeon < totalDungeons - 1 && map[selectedDungeon + 1].isUnlocked()) {
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
        Rectangle doorBox = { (float)map[i].getX() - 35, (float)map[i].getY() - 45, 70, 90 };
        if (GameUI::IsClicked(doorBox)) {
            selectedDungeon = i;
            doorClicked = true;
            break;
        }
    }

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_A) || doorClicked) {
        Dungeon& curr = map[selectedDungeon];

        if (curr.isCleared()) {
            ui.addLog(TextFormat("Dungeon %d is already cleared!", curr.getId()));
        } else if (!curr.isUnlocked()) {
            ui.addLog(TextFormat("Dungeon %d is locked!", curr.getId()));
        } else if (player != nullptr) {
            bool won = curr.fight(*player);

            if (won) {
                curr.setCleared(true);
                if (selectedDungeon + 1 < totalDungeons) {
                    map[selectedDungeon + 1].setUnlocked(true);
                }

                int goldReward = 20 + (selectedDungeon * 15);
                player->increaseGold(goldReward);
                ui.addLog(TextFormat("VICTORY! Dungeon %d Cleared! (+%d Gold)", curr.getId(), goldReward));

                bool allCleared = true;
                for (int i = 0; i < totalDungeons; i++) {
                    if (!map[i].isCleared()) {
                        allCleared = false;
                        break;
                    }
                }
                if (allCleared) {
                    state = WIN;
                }
            } else {
                ui.addLog(TextFormat("DEFEAT in Dungeon %d!", curr.getId()));
                state = GAME_OVER;
            }
        }
    }
}

void Game::updateShop() {
    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_S) || GameUI::IsClicked({ 400, 625, 480, 35 })) {
        state = MAP;
    }

    if (player == nullptr) {
        return;
    }

    if (GameUI::IsClicked({ 140, 180, 300, 70 })) {
        tryPurchasePotion("health", "Health Potion");
    }
    if (GameUI::IsClicked({ 140, 260, 300, 70 })) {
        tryPurchasePotion("strength", "Strength Potion");
    }
    if (GameUI::IsClicked({ 140, 340, 300, 70 })) {
        tryPurchasePotion("resistance", "Resistance Potion");
    }

    if (GameUI::IsClicked({ 640, 180, 380, 70 })) {
        tryPurchaseArmor("chain", "Chain Armor", ownsChainArmor);
    }
    if (GameUI::IsClicked({ 640, 260, 380, 70 })) {
        tryPurchaseArmor("iron", "Iron Armor", ownsIronArmor);
    }
    if (GameUI::IsClicked({ 640, 340, 380, 70 })) {
        tryPurchaseArmor("diamond", "Diamond Armor", ownsDiamondArmor);
    }
    if (GameUI::IsClicked({ 640, 420, 380, 70 })) {
        tryPurchaseArmor("dragon scale", "Dragon Scale", ownsDragonArmor);
    }
}

bool Game::tryPurchasePotion(const std::string& type, const std::string& label) {
    Potion p(type);
    if (player->getGold() < p.getPrice()) {
        ui.addLog("Not enough gold!");
        return false;
    }

    if (type == "health") {
        int healed = player->refillHealth((int)Potion::getEffectFactor("health"));
        player->setGold(player->getGold() - p.getPrice());
        ui.addLog(TextFormat("Bought %s (+%d HP | -%.0f G)", label.c_str(), healed, p.getPrice()));
        return true;
    }

    if (!player->addPotion(p)) {
        ui.addLog("Inventory is full!");
        return false;
    }
    player->setGold(player->getGold() - p.getPrice());
    ui.addLog(TextFormat("Bought %s (-%.0f G)", label.c_str(), p.getPrice()));
    return true;
}

bool Game::tryPurchaseArmor(const std::string& material, const std::string& label, bool& ownedFlag) {
    if (ownedFlag) {
        ui.addLog(TextFormat("You already own %s!", label.c_str()));
        return false;
    }

    Armor a(material);
    if (player->getGold() < a.getPrice()) {
        ui.addLog("Not enough gold!");
        return false;
    }

    player->setGold(player->getGold() - a.getPrice());
    player->increaseArmor((int)a.getBoost());
    ownedFlag = true;
    ui.addLog(TextFormat("Bought %s (+%.0f Armor | -%.0f G)", label.c_str(), a.getBoost(), a.getPrice()));
    return true;
}

void Game::updateGameOver() {
    if (IsKeyPressed(KEY_ONE) || GameUI::IsClicked({ 460, 360, 360, 50 })) {
        resetForNewRun();
    }
    if (IsKeyPressed(KEY_TWO) || GameUI::IsClicked({ 460, 440, 360, 50 })) {
        running = false;
    }
}

void Game::updateWin() {
    if (IsKeyPressed(KEY_ONE) || GameUI::IsClicked({ 460, 360, 360, 50 })) {
        resetForNewRun();
    }
    if (IsKeyPressed(KEY_TWO) || GameUI::IsClicked({ 460, 440, 360, 50 })) {
        running = false;
    }
}

void Game::resetForNewRun() {
    state = MENU;
    heroName = "";
    delete player;
    player = nullptr;
    ui.clearLogs();

    ownsChainArmor = false;
    ownsIronArmor = false;
    ownsDiamondArmor = false;
    ownsDragonArmor = false;
}