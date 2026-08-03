# Dungeons of Agony

A 2D role-playing dungeon crawler written in C++ using the `raylib` library. Choose your hero, explore dungeons, defeat bosses, and upgrade your gear in the merchant shop!

## Prerequisites

To compile and play this game from source, you will need:
* A C++17 compatible compiler (GCC, Clang, or MSVC)
* [raylib](https://www.raylib.com/) installed on your system

## Installing `raylib`

### Windows
The easiest way to set up raylib on Windows is using **vcpkg** or downloading the precompiled binaries for MinGW/Visual Studio from the [raylib releases page](https://github.com/raysan5/raylib/releases).
If using vcpkg:
```bash
vcpkg install raylib
```

### macOS
Use [Homebrew](https://brew.sh/):
```bash
brew install raylib
```

### Linux (Ubuntu/Debian)
Install the required dependencies for raylib:
```bash
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```
Then, clone the raylib repository and build it from source via CMake, or install it via your package manager if available.

## Compiling the Game

Navigate to the project root directory containing the source files (`main.cpp`, `Game.cpp`, etc.) and the `images/` folder.

### Using GCC (g++)
If you have `g++` installed, you can compile the game using the following command (adjust library flags based on your OS setup). Assuming `Items` is a subdirectory for item classes:

**Windows (MinGW):**
```bash
g++ *.cpp Items/*.cpp -o DungeonsOfAgony.exe -O2 -Wall -std=c++17 -Wno-missing-braces -lraylib -lopengl32 -lgdi32 -lwinmm
```

**macOS / Linux:**
```bash
g++ *.cpp Items/*.cpp -o DungeonsOfAgony -O2 -Wall -std=c++17 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
*(Note: On macOS, you may need to use the `-framework OpenGL` and `-framework Cocoa` flags instead of `-lGL` and `-lX11` depending on your brew setup).*

## Running the Game

Once compiled, ensure the `images/` folder (containing textures like `menu-background.png`, `door.png`, `warrior.png`) is accessible. The code checks local and parent directories. 

Run the executable:

**Windows:**
```cmd
.\DungeonsOfAgony.exe
```

**macOS / Linux:**
```bash
./DungeonsOfAgony
```

## How to Play
1. **Main Menu:** Press `1` to start or `2` to read the in-game instructions.
2. **Setup:** Type your character's name, choose a difficulty (Easy, Medium, Hard), and pick your hero class (Warrior, Mage, Assassin).
3. **Map Screen:** 
   - Click on unlocked dungeon doors (D1, D2, etc.) with your mouse.
   - Press `ENTER` to engage in combat and try to clear the dungeon.
   - Arrow keys can also be used to navigate between unlocked dungeons.
4. **Shop:** Press `S` on the map screen to visit the Merchant Shop. Spend your hard-earned gold on Health, Strength, or Resistance potions, or buy better Armor (Chain, Iron, Diamond, Dragon Scale) to survive harder dungeons.
5. **Goal:** Clear all dungeons on the map to achieve victory!
