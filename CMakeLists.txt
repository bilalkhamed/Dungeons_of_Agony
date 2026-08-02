cmake_minimum_required(VERSION 3.20)
project(OOP_Project CXX)

# Lock down modern C++ standard for the team
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Include the FetchContent module (built into CMake)
include(FetchContent)

# 2. Tell CMake to download the raw raylib source files directly (Bypasses Git entirely!)
FetchContent_Declare(
        raylib
        URL      https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)


# 3. macOS Specific Fix: Force raylib to build as a static library
# This prevents code-signing or dynamic library path errors on Apple Silicon Macs
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# 4. Download and make raylib targets available to this project
FetchContent_MakeAvailable(raylib)

# 5. Define your executable with all your team's source files
add_executable(OOP_Project
        main.cpp
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
        GameUI.cpp
)

# 6. Universally link raylib
# raylib's internal scripts will automatically attach the correct Mac/Windows frameworks here!
target_link_libraries(OOP_Project PRIVATE raylib)
