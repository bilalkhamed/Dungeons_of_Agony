#include "GameUI.h"
#include <cmath>
#include "raylib.h"

GameUI::GameUI()
    : menuBgTex{0},
      dungeonBgTex{0},
      shopBgTex{0},
      logoTex{0},
      doorTex{0},
      warriorTex{0},
      mageTex{0},
      assassinTex{0},
      timer(0.0f),
      logCount(0) {}

GameUI::~GameUI() {
    unload();
}

Texture2D GameUI::loadSafeTexture(const string& filename) {
    string searchPaths[] = {
        "images/" + filename,
        "../images/" + filename,
        "../../images/" + filename,
        filename
    };

    for (const auto& path : searchPaths) {
        if (FileExists(path.c_str())) {
            return LoadTexture(path.c_str());
        }
    }
    return Texture2D{ 0 };
}

void GameUI::init() {
    menuBgTex = loadSafeTexture("menu-background.png");
    dungeonBgTex = loadSafeTexture("dungeon-background.png");
    shopBgTex = loadSafeTexture("shop-background.png");
    logoTex = loadSafeTexture("logo.png");
    doorTex = loadSafeTexture("door.png");
    warriorTex = loadSafeTexture("warrior.png");
    mageTex = loadSafeTexture("mage.png");
    assassinTex = loadSafeTexture("assassin.png");
}

void GameUI::unload() {
    if (menuBgTex.id > 0)    { UnloadTexture(menuBgTex); menuBgTex.id = 0; }
    if (dungeonBgTex.id > 0) { UnloadTexture(dungeonBgTex); dungeonBgTex.id = 0; }
    if (shopBgTex.id > 0)    { UnloadTexture(shopBgTex); shopBgTex.id = 0; }
    if (logoTex.id > 0)      { UnloadTexture(logoTex); logoTex.id = 0; }
    if (doorTex.id > 0)      { UnloadTexture(doorTex); doorTex.id = 0; }
    if (warriorTex.id > 0)   { UnloadTexture(warriorTex); warriorTex.id = 0; }
    if (mageTex.id > 0)      { UnloadTexture(mageTex); mageTex.id = 0; }
    if (assassinTex.id > 0)  { UnloadTexture(assassinTex); assassinTex.id = 0; }
}

void GameUI::updateTimer() {
    timer += GetFrameTime() * 5.0f;
}

void GameUI::addLog(const string& text) {
    if (logCount < 4) {
        logs[logCount++] = text;
    } else {
        for (int i = 0; i < 3; i++) {
            logs[i] = logs[i + 1];
        }
        logs[3] = text;
    }
}

void GameUI::clearLogs() {
    logCount = 0;
    for (int i = 0; i < 4; i++) logs[i] = "";
}

bool GameUI::IsHovered(Rectangle rect) {
    return CheckCollisionPointRec(GetMousePosition(), rect);
}

bool GameUI::IsClicked(Rectangle rect) {
    return IsHovered(rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void GameUI::drawBackground(int width, int height, const string& type) {
    Texture2D T = menuBgTex;
    if (type == "DUNGEON" && dungeonBgTex.id > 0) T = dungeonBgTex;

    if (T.id > 0) {
        float scale = (height * 1.0f) / T.height;
        float drawWidth = T.width * scale;
        float drawX = (width - drawWidth) / 2.0f;

        DrawTexturePro(
            T,
            { 0.0f, 0.0f, (T.width * 1.0f), (T.height * 1.0f) },
            { drawX, 0.0f, drawWidth, (height * 1.0f) },
            { 0.0f, 0.0f }, 0.0f, WHITE
        );
    } else {
        DrawRectangleGradientV(0, 0, width, height, Color{ 15, 15, 25, 255 }, Color{ 5, 5, 10, 255 });
    }
}

void GameUI::drawLoadingScreen(int width) {
    if (logoTex.id > 0) {
        float scale = 240.0f / logoTex.width;
        DrawTextureEx(logoTex, { (width - 240.0f) / 2.0f, 150.0f }, 0.0f, scale, WHITE);
    }

    const char* text = "Unlocking the gates. . .";
    int x = (width - MeasureText(text, 22)) / 2;
    DrawRectangle(x - 20, 630, MeasureText(text, 22) + 40, 40, ColorAlpha(BLACK, 0.8f));
    DrawText(text, x, 640, 22, RAYWHITE);
}

void GameUI::drawPressStart(int width) {
    if (logoTex.id > 0) {
        float scale = 240.0f / logoTex.width;
        DrawTextureEx(logoTex, { (width - 240.0f) / 2.0f, 120.0f }, 0.0f, scale, WHITE);
    }

    const char* text = "- PRESS ANY BUTTON TO START -";
    int x = (width - MeasureText(text, 28)) / 2;
    DrawRectangle(x - 20, 630, MeasureText(text, 28) + 40, 45, ColorAlpha(BLACK, 0.85f));
    DrawText(text, x, 640, 28, GOLD);
}

void GameUI::drawMainMenu() {
    if (logoTex.id > 0) {
        float logoWidth = 240.0f;
        float scale = logoWidth / logoTex.width;
        DrawTextureEx(logoTex, { (1280.0f - logoWidth) / 2.0f, 15.0f }, 0.0f, scale, WHITE);
    }

    DrawRectangle(420, 240, 440, 360, ColorAlpha(BLACK, 0.85f));
    DrawText("MAIN MENU", 480, 270, 45, GOLD);

    DrawText("[1] Start Game",  485, 360, 28, IsHovered({ 460, 355, 360, 45 }) ? GREEN : WHITE);
    DrawText("[2] How To Play", 485, 430, 28, IsHovered({ 460, 425, 360, 45 }) ? GREEN : WHITE);
    DrawText("[3] Quit",        485, 500, 28, IsHovered({ 460, 495, 360, 45 }) ? RED   : WHITE);
}

void GameUI::drawHowToPlay() {
    DrawRectangle(350, 180, 580, 360, ColorAlpha(BLACK, 0.85f));
    DrawText("HOW TO PLAY", 500, 120, 45, GOLD);
    DrawText("- Choose your hero name and class", 380, 240, 22, WHITE);
    DrawText("- Select unlocked doors on the map", 380, 300, 22, WHITE);
    DrawText("- Click or press [ENTER] to fight", 380, 360, 22, WHITE);
    DrawText("- Visit shop to buy items (Potions, armor)", 380, 420, 22, WHITE);
    DrawText("Click or press [BACKSPACE] to return", 420, 605, 20, IsHovered({ 420, 600, 380, 30 }) ? GREEN : GRAY);
}

void GameUI::drawNameEntry(const string &text) {
    DrawRectangle(350, 180, 580, 360, ColorAlpha(BLACK, 0.85f));
    DrawText("ENTER YOUR NAME:", 450, 220, 35, GOLD);
    DrawRectangleLines(460, 320, 360, 70, LIGHTGRAY);
    DrawText(text.c_str(), 490, 340, 35, GREEN);
    DrawText("Click or press [ENTER] to confirm", 440, 465, 22, IsHovered({ 460, 460, 360, 40 }) ? GREEN : GRAY);
}

void GameUI::drawDifficultySelection() {
    DrawRectangle(350, 180, 580, 420, ColorAlpha(BLACK, 0.85f));
    DrawText("SELECT DIFFICULTY", 410, 190, 40, GOLD);
    DrawText("[1] EASY   (3 Dungeons)",  460, 280, 26, IsHovered({ 440, 270, 400, 50 }) ? GREEN  : WHITE);
    DrawText("[2] MEDIUM (6 Dungeons)",  460, 350, 26, IsHovered({ 440, 340, 400, 50 }) ? YELLOW : WHITE);
    DrawText("[3] HARD   (10 Dungeons)", 460, 420, 26, IsHovered({ 440, 410, 400, 50 }) ? RED    : WHITE);
}

void GameUI::drawClassSelection() {
    DrawRectangle(80, 40, 1120, 640, ColorAlpha(BLACK, 0.85f));
    DrawText("CHOOSE YOUR HERO CLASS", 360, 60, 40, GOLD);

    auto drawCard = [](Rectangle c, Color b, const char* title, Texture2D portrait, const char* hp, const char* dmg, const char* arm) {
        DrawRectangleRec(c, ColorAlpha(BLACK, 0.8f));
        DrawRectangleLinesEx(c, 4, b);

        if (portrait.id > 0) {
            Rectangle portraitArea = { c.x + 15, c.y + 15, c.width - 30, 230 };
            DrawTexturePro(portrait,
                { 0, 0, (float)portrait.width, (float)portrait.height },
                portraitArea, { 0, 0 }, 0.0f, WHITE);
            DrawRectangleLinesEx(portraitArea, 2, b);
        }

        DrawText(title, c.x + 25, c.y + 260, 24, b);
        DrawText(hp,    c.x + 30, c.y + 310, 22, WHITE);
        DrawText(dmg,   c.x + 30, c.y + 350, 22, WHITE);
        DrawText(arm,   c.x + 30, c.y + 390, 22, WHITE);
    };

    drawCard({ 140, 140, 280, 480 }, IsHovered({ 140, 140, 280, 480 }) ? WHITE : RED,   "[1] WARRIOR",  warriorTex,  "HP:  150", "DMG: 10", "ARM: 5");
    drawCard({ 500, 140, 280, 480 }, IsHovered({ 500, 140, 280, 480 }) ? WHITE : BLUE,  "[2] MAGE",     mageTex,     "HP:  50",  "DMG: 20", "ARM: 0");
    drawCard({ 860, 140, 280, 480 }, IsHovered({ 860, 140, 280, 480 }) ? WHITE : GREEN, "[3] ASSASSIN", assassinTex, "HP:  100", "DMG: 15", "ARM: 0");
}

void GameUI::drawMapScreen(Player* player, const std::string& name, const std::string& heroClass, int maxHp, Dungeon map[], int totalDungeons, int selectedIndex) {
    for (int i = 0; i < totalDungeons - 1; i++) {
        Color lineCol = map[i + 1].isUnlocked() ? GOLD : GRAY;
        DrawLineEx(
            { (float)map[i].getX(), (float)map[i].getY() },
            { (float)map[i + 1].getX(), (float)map[i + 1].getY() },
            6, BLACK
        );
        DrawLineEx(
            { (float)map[i].getX(), (float)map[i].getY() },
            { (float)map[i + 1].getX(), (float)map[i + 1].getY() },
            3, lineCol
        );
    }

    for (int i = 0; i < totalDungeons; i++) {
        int posX = map[i].getX();
        int posY = map[i].getY();
        Rectangle doorRect = { (float)(posX - 35), (float)(posY - 45), 70.0f, 90.0f };

        Color doorTint = map[i].isCleared() ? ColorAlpha(GREEN, 0.9f) : (map[i].isUnlocked() ? WHITE : Color{ 100, 100, 110, 255 });

        if (doorTex.id > 0) {
            DrawTexturePro(doorTex, { 0, 0, (float)doorTex.width, (float)doorTex.height }, doorRect, { 0, 0 }, 0.0f, doorTint);
        } else {
            Color fill = map[i].isCleared() ? Color{ 40, 120, 50, 255 } : (map[i].isUnlocked() ? Color{ 130, 80, 40, 255 } : Color{ 50, 50, 60, 255 });
            Color border = map[i].isCleared() ? GREEN : (map[i].isUnlocked() ? GOLD : GRAY);

            DrawRectangleRec(doorRect, fill);
            DrawRectangleLinesEx(doorRect, 3, border);
            DrawCircle(posX + 20, posY, 4, map[i].isUnlocked() ? GOLD : LIGHTGRAY);
        }

        if (i == selectedIndex) {
            DrawRectangleLinesEx({ doorRect.x - 4, doorRect.y - 4, doorRect.width + 8, doorRect.height + 8 }, 3, GOLD);
        }

        DrawText(TextFormat("D%d", map[i].getId()), posX - 12, posY + 52, 18, RAYWHITE);
    }

    int currX = map[selectedIndex].getX();
    int currY = map[selectedIndex].getY();

    DrawTriangle(
        { (float)currX, (float)(currY - 55) },
        { (float)(currX + 14), (float)(currY - 78) },
        { (float)(currX - 14), (float)(currY - 78) },
        GOLD
    );
    DrawTriangleLines(
        { (float)currX, (float)(currY - 55) },
        { (float)(currX + 14), (float)(currY - 78) },
        { (float)(currX - 14), (float)(currY - 78) },
        ORANGE
    );

    const Dungeon& selected = map[selectedIndex];
    Entity boss = selected.getBoss();

    DrawRectangle(440, 520, 400, 100, ColorAlpha(BLACK, 0.85f));
    DrawRectangleLines(440, 520, 400, 100, GOLD);

    DrawText(TextFormat("Dungeon %d (Level %d)", selected.getId(), selectedIndex + 1), 460, 530, 20, GOLD);
    DrawText(TextFormat("Boss Health: %d", boss.getHp()), 460, 560, 18, RAYWHITE);
    DrawText(TextFormat("Boss Damage: %d", boss.getDamage()), 460, 585, 18, RED);

    DrawRectangle(0, 0, 1280, 50, ColorAlpha(BLACK, 0.7f));
    DrawText(TextFormat("%s (%s)", name.c_str(), heroClass.c_str()), 20, 15, 20, GOLD);
    DrawText(TextFormat("HP: %d/%d", player->getHp(), maxHp), 300, 15, 20, GREEN);
    DrawText(TextFormat("Gold: %.0f G", player->getGold()), 500, 15, 20, YELLOW);
    DrawText("Press [S] for Shop | [ENTER] to Enter Dungeon", 760, 15, 18, GRAY);
}

void GameUI::drawShopScreen(Player* p) {
    Rectangle shopBox = { 100, 40, 1080, 640 };

    if (shopBgTex.id > 0) {
        DrawTexturePro(shopBgTex,
            { 0.0f, 0.0f, (float)shopBgTex.width, (float)shopBgTex.height },
            shopBox, { 0.0f, 0.0f }, 0.0f, WHITE);
        DrawRectangleRec(shopBox, ColorAlpha(BLACK, 0.65f));
    } else {
        DrawRectangleRec(shopBox, ColorAlpha(BLACK, 0.92f));
    }

    DrawRectangleLinesEx(shopBox, 3, GOLD);

    DrawText("MERCHANT SHOP", 480, 60, 36, GOLD);
    DrawText(TextFormat("Your Gold: %.0f G", p->getGold()), 490, 105, 22, YELLOW);

    DrawText("--- POTIONS ---", 220, 140, 22, GREEN);

    auto drawShopItem = [this](Rectangle rect, const char* name, const char* effect, double price, Color theme) {
        DrawRectangleRec(rect, ColorAlpha(BLACK, 0.75f));
        DrawRectangleLinesEx(rect, 2, IsHovered(rect) ? WHITE : theme);
        DrawText(name, rect.x + 15, rect.y + 12, 20, theme);
        DrawText(effect, rect.x + 15, rect.y + 38, 15, GRAY);
        DrawText(TextFormat("%.0f G", price), rect.x + 210, rect.y + 24, 20, YELLOW);
    };

    drawShopItem({ 140, 180, 300, 70 }, "Health Potion", "+20 HP", 5, GREEN);
    drawShopItem({ 140, 260, 300, 70 }, "Strength Potion", "+3 Damage", 10, RED);
    drawShopItem({ 140, 340, 300, 70 }, "Resistance Potion", "+1 Armor", 15, BLUE);

    DrawText("--- ARMORS ---", 740, 140, 22, BLUE);
    drawShopItem({ 640, 180, 380, 70 }, "Chain Armor", "+25 Armor", 10, LIGHTGRAY);
    drawShopItem({ 640, 260, 380, 70 }, "Iron Armor", "+50 Armor", 18, SKYBLUE);
    drawShopItem({ 640, 340, 380, 70 }, "Diamond Armor", "+80 Armor", 30, Color{ 0, 228, 255, 255 });
    drawShopItem({ 640, 420, 380, 70 }, "Dragon Scale", "+150 Armor", 150, ORANGE);

    DrawRectangle(200, 520, 880, 60, ColorAlpha(BLACK, 0.85f));
    int logY = 530;
    for (int i = 0; i < logCount; i++) {
        DrawText(logs[i].c_str(), 220, logY, 16, RAYWHITE);
        logY += 22;
    }
    DrawText("Click item to Buy | Press [BACKSPACE] or [S] to Return", 370, 630, 20, IsHovered({ 400, 625, 480, 30 }) ? GREEN : GRAY);
}

void GameUI::drawGameOverScreen() {
    DrawRectangle(380, 180, 520, 360, ColorAlpha(BLACK, 0.92f));
    DrawRectangleLinesEx({ 380, 180, 520, 360 }, 4, RED);
    DrawText("YOU DIED", 510, 230, 50, RED);
    DrawText("Your journey ends here...", 495, 300, 22, GRAY);
    DrawText("[1] Restart", 550, 372, 28, IsHovered({ 460, 360, 360, 50 }) ? GREEN : WHITE);
    DrawText("[2] Quit",    570, 452, 28, IsHovered({ 460, 440, 360, 50 }) ? RED   : WHITE);
}

void GameUI::drawWinScreen() {
    DrawRectangle(380, 180, 520, 360, ColorAlpha(BLACK, 0.92f));
    DrawRectangleLinesEx({ 380, 180, 520, 360 }, 4, GOLD);
    DrawText("VICTORY!", 510, 230, 50, GOLD);
    DrawText("Every dungeon lies cleared.", 490, 300, 22, GRAY);
    DrawText("[1] Restart", 550, 372, 28, IsHovered({ 460, 360, 360, 50 }) ? GREEN : WHITE);
    DrawText("[2] Quit",    570, 452, 28, IsHovered({ 460, 440, 360, 50 }) ? RED   : WHITE);
}