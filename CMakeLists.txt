#cmake_minimum_required(VERSION 4.2)
#project(OOP_Project)
#
#set(CMAKE_CXX_STANDARD 26)
#
#add_executable(OOP_Project main.cpp
#        Entity.cpp
#        Entity.h
#        Player.cpp
#        Player.h
#        CharacterTypes.h
#        CharacterTypes.cpp
#        Items/Item.cpp
#        Items/Item.h
#        Items/Potion.cpp
#        Items/Potion.h
#        Items/Armor.cpp
#        Items/Armor.h
#        Dungeon.cpp
#        Dungeon.h)

cmake_minimum_required(VERSION 3.20)
project(OOP_Project CXX)

set(CMAKE_CXX_STANDARD 17)

# 1. Tell CMake where to look for Homebrew packages on both Apple Silicon and Intel Macs
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew" "/usr/local")

# 2. Find the raylib package
find_package(raylib REQUIRED)

# 3. Define your executable (replace main.cpp if your source file has a different name)
add_executable(OOP_Project main.cpp
                Entity.cpp
                Entity.h
                Player.cpp
                Player.h
                CharacterTypes.h
                CharacterTypes.cpp
                Items/Item.cpp
                Items/Item.h
                Items/Potion.cpp
                Items/Potion.h
                Items/Armor.cpp
                Items/Armor.h
                Dungeon.cpp
                Dungeon.h
        GameUI.h
        GameUI.cpp)

# 4. Link raylib and native macOS frameworks to your executable
target_link_libraries(OOP_Project PRIVATE
raylib
"-framework OpenGL"
"-framework Cocoa"
"-framework IOKit"
"-framework CoreVideo")