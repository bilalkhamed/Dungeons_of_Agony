#include "GameUI.h"
#include <raylib.h>
#include <cmath>

const string GameUI::MENU_BG_SRC = "../images/menu-background.png";
const string GameUI::DUNGEON_BG_SRC = "../images/dungeon-background.png";

GameUI::GameUI(): texture{0}, timer(0.0f), logCount(0) {}

GameUI::~GameUI() {
    unload(); // Cleaning up resources
}

// FileExists(filepath)
// returns true if file exists in given path
void GameUI::init() {
    ChangeDirectory(GetApplicationDirectory());
    if (FileExists(GameUI::MENU_BG_SRC.c_str())) {
        texture = LoadTexture(MENU_BG_SRC.c_str());
    }
}

void GameUI::unload() {
    // Greater than 0 means an image has been loaded
    // Which returns true
    if (texture.id > 0) {
        // UnloadTexture(Texture2D smth)
        // Just like DMA we need to unload it to prevent memory leaks
        UnloadTexture(texture);
        texture.id = 0; // Unloaded state, Important
    }
}

void GameUI::updateTimer() {
    // GetFrameTime()
    // Returns a float (Time between last frame and current frame for 60 FPS)
    // Times 5.0f to speed up the UI and animation physics
    timer += GetFrameTime() * 5.0f;
}

void GameUI::addLog(const string& text) {
    if (logCount < 4) {
        logs[logCount++] = text;
    }
    else {
        // Shift messages up by 1 position (rolling log effect)
        for (int i = 0; i < 3; i++) {
            logs[i] = logs[i+1];
        }
        logs[3] = text; // Put newest message at the bottom
    }
}

void GameUI::clearLogs() {
    logCount = 0;
    for (int i = 0; i < 4; i++) {
        logs[i] = "";
    }
}

// For the mouse
bool GameUI::IsHovered(Rectangle rect) {
    // GetMousePosition()
    // Returns x & y cords for the mouse

    // CheckCollisionPointRec(point, Rectangle rec)
    // returns true if the mouse cords is inside the rect to make the UI more interactive with the mouse
    return CheckCollisionPointRec(GetMousePosition(), rect);
}

// For the mouse
bool GameUI::IsClicked(Rectangle rect) {
    // IsMouseButtonPressed(int button)
    // Checks if the mouse button (button) was clicked inside a rect
    // and returns true if it did
    return IsHovered(rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void GameUI::drawBackground(int width, int height) {
    if (texture.id > 0) { // Check if there's a picture
        // 1.0f --> float conversion to avoid integer division truncation
        float scale = (height * 1.0f) / texture.height;
        float width2 = texture.width * scale;
        float x_ = (width - width2) / 2.0f;

        // DrawTexturePro(texture, sourceRect, destRect, origin, rotation, tint)
        // Draws scaled image texture fitted to screen
        DrawTexturePro(texture,
                       { 0.0f, 0.0f, (texture.width * 1.0f), (texture.height * 1.0f) },
                       { x_, 0.0f, width2, (height * 1.0f) },
                       { 0.0f, 0.0f }, 0.0f, WHITE);
    }
    else {
        // DrawRectangleGradientV(x, y, width, height, color1, color2)
        // Smooth vertical gradient fallback when background image is missing
        DrawRectangleGradientV(0, 0, width, height, Color{15, 15, 25, 255}, Color{5, 5, 10, 255});
    }
}

void GameUI::drawLoadingScreen(int width) {
    const char* text = "Unlocking the gates. . .";
    // MeasureText(const char* txt, fontsize)
    // Returns horizontal width of text in pixels
    int x = (width - MeasureText(text, 22)) / 2;

    // ColorAlpha(color, float)
    // Background overlays with opacity factor
    DrawRectangle(x - 20, 630, MeasureText(text, 22) + 40, 40, ColorAlpha(BLACK, 0.8f));

    // DrawText(text, x, y, fontsize, color)
    // Just like cout to draw stuff outside onto the screen
    DrawText(text, x, 640, 22, RAYWHITE);
}

void GameUI::drawPressStart(int width) {
    const char* text = "- STRIKE ANY BUTTON TO START -";
    int x = (width - MeasureText(text, 28)) / 2;
    DrawRectangle(x - 20, 630, MeasureText(text, 28) + 40, 45, ColorAlpha(BLACK, 0.85f));
    DrawText(text, x, 640, 28, GOLD);
}

void GameUI::drawMainMenu() {
    DrawRectangle(420, 150, 440, 380, ColorAlpha(BLACK, 0.85f));
    DrawText("MAIN MENU", 480, 190, 45, GOLD);

    // Ternary hover check: IsHovered({x, y, w, h}) ? hoverColor : normalColor
    DrawText("[1] Start Game",  485, 295, 28, IsHovered({ 460, 290, 360, 45 }) ? GREEN : WHITE);
    DrawText("[2] How To Play", 485, 365, 28, IsHovered({ 460, 360, 360, 45 }) ? GREEN : WHITE);
    DrawText("[3] Quit",        485, 435, 28, IsHovered({ 460, 430, 360, 45 }) ? RED   : WHITE); // Red makes more sense for a quit button
}

void GameUI::drawHowToPlay() {
    DrawRectangle(350, 180, 580, 360, ColorAlpha(BLACK, 0.85f));
    DrawText("HOW TO PLAY", 500, 120, 45, GOLD);
    DrawText("- Choose your hero name and class", 380, 240, 22, WHITE);
    DrawText("- Select unlocked doors on the map", 380, 300, 22, WHITE);
    DrawText("- Fight monsters directly inside doors", 380, 360, 22, WHITE);
    DrawText("- Visit shop to buy items (Potions, armor)", 380, 420, 22, WHITE);
    DrawText("Click or press [BACKSPACE] to return", 420, 605, 20, IsHovered({ 420, 600, 380, 30 }) ? GREEN : GRAY);
}

void GameUI::drawNameEntry(const string &text) {
    DrawRectangle(350, 180, 580, 360, ColorAlpha(BLACK, 0.85f));
    DrawText("ENTER YOUR NAME:", 450, 220, 35, GOLD);

    // DrawRectangleLines(x, y, width, height, color)
    // Thin outline borders for input boxes
    DrawRectangleLines(460, 320, 360, 70, LIGHTGRAY);

    // text.c_str() converts C++ std::string to const char* required by Raylib
    DrawText(text.c_str(), 490, 340, 35, GREEN);
    DrawText("Click or press [ENTER] to confirm", 440, 465, 22, IsHovered({460, 460, 360, 40}) ? GREEN : GRAY);
}

void GameUI::drawDifficultySelection() {
    DrawRectangle(350, 180, 580, 420, ColorAlpha(BLACK, 0.85f));
    DrawText("SELECT DIFFICULTY", 410, 190, 40, GOLD);
    DrawText("[1] EASY   (3 Dungeons)",  460, 280, 26, IsHovered({ 440, 270, 400, 50 }) ? GREEN  : WHITE);
    DrawText("[2] MEDIUM (6 Dungeons)",  460, 350, 26, IsHovered({ 440, 340, 400, 50 }) ? YELLOW : WHITE);
    DrawText("[3] HARD   (10 Dungeons)", 460, 420, 26, IsHovered({ 440, 410, 400, 50 }) ? RED    : WHITE);
}

void GameUI::drawClassSelection() {
    if (FileExists(GameUI::MENU_BG_SRC.c_str())) {
        texture = LoadTexture(MENU_BG_SRC.c_str());
    }
    DrawRectangle(80, 50, 1120, 620, ColorAlpha(BLACK, 0.85f));
    DrawText("CHOOSE YOUR HERO CLASS", 360, 100, 40, GOLD);

    // C++ Lambda Function to modularize repeated drawing code for hero selection cards
    auto Card = [](Rectangle c, Color b, const char* t, const char* hp, const char* dmg, const char* arm) {
        // DrawRectangleRec(Rectangle rec, Color color)
        // Used for: Drawing filled panels using a Rectangle struct directly
        DrawRectangleRec(c, ColorAlpha(BLACK, 0.7f));

        // DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color)
        // Used for: Drawing customizable thick borders around UI selection boxes
        DrawRectangleLinesEx(c, 4, b);
        DrawText(t,   c.x + 30, c.y + 30,  26, b);
        DrawText(hp,  c.x + 40, c.y + 120, 24, WHITE);
        DrawText(dmg, c.x + 40, c.y + 180, 24, WHITE);
        DrawText(arm, c.x + 40, c.y + 240, 24, WHITE);
    };

    Card({ 140, 200, 280, 400 }, IsHovered({ 140, 200, 280, 400 }) ? WHITE : RED,   "[1] WARRIOR",  "HP:  150", "DMG: 10", "ARM: 5");
    Card({ 500, 200, 280, 400 }, IsHovered({ 500, 200, 280, 400 }) ? WHITE : BLUE,  "[2] MAGE",     "HP:  50",  "DMG: 20", "ARM: 0");
    Card({ 860, 200, 280, 400 }, IsHovered({ 860, 200, 280, 400 }) ? WHITE : GREEN, "[3] ASSASSIN", "HP:  100", "DMG: 15", "ARM: 0");
}

void GameUI::drawMapScreen(Player *p, const string &name, const string &className, int maxHp, Dungeon map[], int totalDungeons, int selectedInDungeon, bool isInCombat, int EnemyMaxHp) {
    if (FileExists(GameUI::DUNGEON_BG_SRC.c_str())) {
        texture = LoadTexture(DUNGEON_BG_SRC.c_str());
    }
    // Player Stats HUD Panel
    DrawRectangle(20, 20, 320, 180, ColorAlpha(BLACK, 0.85f));
    DrawRectangleLinesEx({20, 20, 320, 180}, 2, GOLD);

    // TextFormat(format, ...)
    // Works like printf to format variables directly into C-strings
    DrawText(name.c_str(), 35, 32, 22, GOLD);
    DrawText(TextFormat("Class: %s", className.c_str()), 35, 62, 18, WHITE);
    DrawText(TextFormat("HP: %d/%d", p->getHp(), maxHp), 35, 92, 18, RED);
    DrawText(TextFormat("Gold: %.0f", p->getGold()), 35, 122, 18, YELLOW);
    DrawText(TextFormat("Armor: %d | DMG: %d", p->getArmor(), p->getDamage()), 35, 150, 18, BLUE);

    // Draw connection lines between dungeon nodes
    for (int i = 0; i < totalDungeons - 1; i++) {
        Color lineCol = map[i + 1].isUnlocked ? GOLD : DARKGRAY;
        // DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color)
        // Connects map nodes with thick lines
        DrawLineEx({(map[i].x * 1.0f), (map[i].y * 1.0f)}, {(map[i + 1].x * 1.0f), (map[i + 1].y * 1.0f)}, 4, lineCol);
    }

    // Draw dungeon door nodes
    for (int i = 0; i < totalDungeons; i++) {
        int x = map[i].x, y = map[i].y;
        Color doorCol = DARKGRAY, borderCol = GRAY;
        if (map[i].isCleared)       { doorCol = ColorAlpha(GREEN, 0.4f); borderCol = GREEN; }
        else if (map[i].isUnlocked) { doorCol = ColorAlpha(BLACK, 0.85f); borderCol = WHITE; }
        if (i == selectedInDungeon) { borderCol = GOLD; }

        DrawRectangle(x - 30, y - 40, 60, 80, doorCol);

        // DrawCircle(centerX, centerY, radius, color)
        // Draws filled circle for door arch top
        DrawCircle(x, y - 40, 30, doorCol);
        DrawRectangleLinesEx({(float)x - 30, (float)y - 40, 60, 80}, 3, borderCol);

        // DrawCircleLines(centerX, centerY, radius, color)
        // Draws outline circle for door arch border
        DrawCircleLines(x, y - 40, 30, borderCol);
        DrawCircle(x + 18, y, 4, borderCol); // Door handle knob
        DrawText(TextFormat("D%d", map[i].id), x - 12, y - 20, 20, RAYWHITE);

        if (map[i].isCleared) {
            DrawRectangle(x - 32, y + 48, 64, 20, ColorAlpha(BLACK, 0.8f));
            DrawText("CLEARED", x - 28, y + 51, 12, GREEN);
        } else if (!map[i].isUnlocked) {
            DrawRectangle(x - 28, y + 48, 56, 20, ColorAlpha(BLACK, 0.8f));
            DrawText("LOCKED", x - 22, y + 51, 12, RED);
        }
    }

    // Animated floating selection pointer arrow above selected node
    int currX = map[selectedInDungeon].x, currY = map[selectedInDungeon].y;
    // sinf(timer)
    // Math sine wave creates a smooth bouncing floating animation
    float floatOffset = sinf(timer) * 8.0f;

    // DrawTriangle(v1, v2, v3, color)
    // Draws filled 3-point shape for pointer arrow
    DrawTriangle({(float)currX, (float)currY - 80 - floatOffset},
                 {(float)currX - 12, (float)currY - 105 - floatOffset},
                 {(float)currX + 12, (float)currY - 105 - floatOffset}, GOLD);
    DrawCircle(currX, (int)((float)currY - 110 - floatOffset), 6, GOLD);

    // Bottom Action / Combat Log Panel
    DrawRectangle(360, 540, 560, 150, ColorAlpha(BLACK, 0.9f));
    DrawRectangleLinesEx({360, 540, 560, 150}, 2, isInCombat ? RED : GOLD);

    if (isInCombat) {
        Entity* boss = map[selectedInDungeon].Boss;
        DrawText(TextFormat("ENEMY: Dungeon Boss | HP: %d/%d", boss->getHp(), EnemyMaxHp), 380, 555, 18, RED);
        int logY = 588;
        for (int i = 0; i < logCount; i++) {
            DrawText(logs[i].c_str(), 380, logY, 16, RAYWHITE);
            logY += 25;
        }
        DrawText("[A] Attack   [M] Flee", 380, 665, 15, GREEN);
    } else {
        DrawText("DUNGEON MAP NAVIGATION", 380, 555, 20, GOLD);
        DrawText("Use [LEFT/RIGHT] or Click Door to Select | [ENTER] to Fight", 380, 590, 16, WHITE);
        DrawText("[S] Open Merchant Shop", 380, 620, 18, YELLOW);
        int logY = 650;
        for (int i = 0; i < logCount; i++) {
            DrawText(logs[i].c_str(), 380, logY, 15, RAYWHITE);
            logY += 20;
        }
    }
}

void GameUI::drawShopScreen(Player* p) {
    DrawRectangle(100, 40, 1080, 640, ColorAlpha(BLACK, 0.92f));
    DrawRectangleLinesEx({100, 40, 1080, 640}, 3, GOLD);

    DrawText("MERCHANT SHOP", 480, 60, 36, GOLD);
    DrawText(TextFormat("Your Gold: %.0f G", p->getGold()), 490, 105, 22, YELLOW);

    DrawText("--- POTIONS ---", 220, 140, 22, GREEN);

    // Lambda helper function to render item buttons inside shop screen
    auto DrawShopItem = [this](Rectangle rect, const char* name, const char* effect, double price, Color theme) {
        DrawRectangleRec(rect, ColorAlpha(BLACK, 0.6f));
        DrawRectangleLinesEx(rect, 2, IsHovered(rect) ? WHITE : theme);
        DrawText(name, rect.x + 15, rect.y + 12, 20, theme);
        DrawText(effect, rect.x + 15, rect.y + 38, 15, GRAY);
        DrawText(TextFormat("%.0f G", price), rect.x + 210, rect.y + 24, 20, YELLOW);
    };

    DrawShopItem({ 140, 180, 300, 70 }, "Health Potion", "+20 HP", 5, GREEN);
    DrawShopItem({ 140, 260, 300, 70 }, "Strength Potion", "+3 Damage", 10, RED);
    DrawShopItem({ 140, 340, 300, 70 }, "Resistance Potion", "+1 Armor", 15, BLUE);

    DrawText("--- ARMORS ---", 740, 140, 22, BLUE);
    DrawShopItem({ 640, 180, 380, 70 }, "Chain Armor", "+25 Armor", 10, LIGHTGRAY);
    DrawShopItem({ 640, 260, 380, 70 }, "Iron Armor", "+50 Armor", 18, SKYBLUE);
    DrawShopItem({ 640, 340, 380, 70 }, "Diamond Armor", "+80 Armor", 30, Color{0, 228, 255, 255});
    DrawShopItem({ 640, 420, 380, 70 }, "Dragon Scale", "+150 Armor", 150, ORANGE);

    DrawRectangle(200, 520, 880, 60, ColorAlpha(BLACK, 0.8f));
    int logY = 530;
    for (int i = 0; i < logCount; i++) {
        DrawText(logs[i].c_str(), 220, logY, 16, RAYWHITE);
        logY += 22;
    }
    DrawText("Click item to Buy | Press [BACKSPACE] or [S] to Return", 370, 630, 20, IsHovered({400, 625, 480, 30}) ? GREEN : GRAY);
}

void GameUI::drawGameOverScreen() {
    DrawRectangle(380, 180, 520, 360, ColorAlpha(BLACK, 0.92f));
    DrawRectangleLinesEx({380, 180, 520, 360}, 4, RED);
    DrawText("YOU DIED", 510, 230, 50, RED);
    DrawText("Your journey ends here...", 495, 300, 22, GRAY);
    DrawText("[1] Restart", 550, 372, 28, IsHovered({ 460, 360, 360, 50 }) ? GREEN : WHITE);
    DrawText("[2] Quit",    570, 452, 28, IsHovered({ 460, 440, 360, 50 }) ? RED   : WHITE);
}