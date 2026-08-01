#include "GameUI.h"
#include <raylib.h>
#include <cmath>

GameUI::GameUI(): texture{0}, timer(0.0f), logCount(0) {}

GameUI::~GameUI() {
    unload(); // Cleaning up resources
}

// FileExists(filepath)
// return true if file exists in given path
void GameUI::init(const char* imagePath) {
    if (FileExists(imagePath)) {
        // LoadTexture(filepath)
        // returns a Texture2D that has the following attributes:
        // 1. Id, Width, Height, mipmaps
        // Uploads images
        texture = LoadTexture(imagePath);
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
    // Times 5.0 to speed up the UI and animation physics
    timer += GetFrameTime() * 5.0f;
}

void GameUI::addLog(const string& text) {
    if (logCount < 4) {
        logs[logCount++] = text;
    }
    else {
        for (int i = 0; i < 3, i++) {
            logs[i] = logs[i+1]
        }
        logs[3] = text;
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


void GameUI::drawBackground(width, height) {
    if (texture.id > 0) { // Check if there's a picture
        // 1.0f --> float
        float scale = (height * 1.0f) / texture.height;
        float width2 = texture.width * scale;
        float x_ = (width - width2) / 2.0f;
        /*
         * RAYLIB: DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint)
         * - Parameter 'texture': The loaded image texture to render.
         * - Parameter 'source': Rectangle defining which part of the original image to clip/draw.
         * - Parameter 'dest': Rectangle defining on-screen position and scaled dimensions {x, y, w, h}.
         * - Parameter 'origin': Pivot point for scaling/rotation relative to dest rect (e.g., {0.0f, 0.0f} for top-left).
         * - Parameter 'rotation': Angle in degrees to rotate texture (0.0f = no rotation).
         * - Parameter 'tint': Color multiplier overlay (WHITE = original unmodified image colors).
         * - Used for: Drawing custom scaled background image fitted perfectly to screen.
         */
        drawTexturePro(texture,
                       { 0.0f, 0.0f, (texture.width * 1.0f), (texture.height * 1.0f) },
                       { x_, 0.0f, width2, (height * 1.0f) },
                       { 0.0f, 0.0f }, 0.0f, WHITE);
    }
    else {
        // DrawRectangleGradient(x, y, width, height, color1, color2)
        // Smooth gradient color
        DrawRectangleGradient(0, 0, width, height, color{15, 15, 25, 255}, Color{5, 5, 10, 255});
    }
}

void GameUI::drawLoadingScreen(int width) {
    const char* text = "Unlocking the gates. . .";
    // MeasureText(const char* txt, fontsize)
    // Returns horizontal width of text in pixels
    int x = (width - MeasureText(text, 22)) / 2;

    // ColorAlpha(color, float)
    // Background overlays
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

    DrawText("[1] Start Game", 485, 295, IsHovered({ 460, 290, 360, 45 }) ? GREEN : WHITE);
    DrawText("[2] How To Play", 485, 365, IsHovered({ 460, 360, 360, 45 }) ? GREEN : WHITE);
    DrawText("[3] Quit", 485, 435, IsHovered({ 460, 430, 360, 45 }) ? RED : WHITE); // Red makes more sense for a quit button
}

void GameUI::drawHowToPlay() {
    DrawRectangle(350, 180, 580, 360, ColorAlpha(BLACK, 0.85f));
    DrawText("HOW TO PLAY", 500, 120, 45, GOLD);
    DrawText("- Choose your hero name and class", 380, 240, 22, WHITE);
    DrawText("- Choose your hero name and class", 380,240,22, WHITE);
    DrawText("- Select unlocked doors on the map", 380, 300, 22, WHITE);
    DrawText("- Fight monsters directly inside doors", 380, 360, 22, WHITE);
    DrawText("- Visit shop to but items (Potions, armor)", 380, 420, 22, WHITE);
    DrawText("Click or press [BACKSPACE] to return",420, 605, 20, IsHovered() ? GREEN : GRAY);
}

void GameUI::drawNameEntry(const string &text) {
    DrawRectangle(350, 180, 580, 360, ColorAlpha(BLACK, 0.85f));
    DrawText("ENTER YOUR NAME:", 450, 220, 35, GOLD);
    // DrawRectangleLines(x, y, width, height, color)
    // thin outline borders for input boxes
    DrawRectangleLines(460, 320, 360, 70, LIGHTGRAY);
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
    DrawRectangle(80, 50, 1120, 620, ColorAlpha(BLACK, 0.85f));
    DrawText("CHOOSE YOUR HERO CLASS", 360, 100, 40, GOLD);

    // C++ Lambda Function to modularize repeated drawing code for hero selection cards
    auto Card = [](Rectangle c, Color b, const char* t, const char* hp, const char* dmg, const char* arm) {
         // DrawRectangleRec(Rectangle rec, Color color)
         // Used for: Drawing filled panels using a Rectangle struct directly.
        DrawRectangleRec(c, ColorAlpha(BLACK, 0.7f));


         //DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color
         * - Used for: Drawing customizable thick borders around UI selection boxes.

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
    DrawRectangle(20, 20, 320, 180, ColorAlpha(BLACK, 0.85f));
    DrawRecangleLines({20, 20, 320, 180}, 2, GOLD);

    DrawText(name.c_str(), 35, 32, 22, GOLD);
    DrawText(TextFormat("Class: %s", className.c_str()), 35, 62, 18, WHITE);
    DrawText(TextFormat("HP: %d/%d", p->getHp(), maxHp), 35, 92, 18, RED);
    DrawText(TextFormat("Gold: %.0f", p->getGold()), 35, 122, 18, YELLOW);
    DrawText(TextFormat("Armor: %d | DMG: %d", p->getArmor(), p->getDamage()), 35, 150, 18, BLUE);

    for (int i = 0; i <totalDungeons - 1; i++) {
        // DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color)
        DrawLineEx({(map[i].x * 1.0f), (map[i].y * 1.0f)}, {(map[i + 1].x * 1.0f), (map[i + 1].y * 1.0f)}, 4, lineCol);
    }


    
}
