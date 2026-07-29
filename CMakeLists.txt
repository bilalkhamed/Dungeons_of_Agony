cmake_minimum_required(VERSION 4.2)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 26)

add_executable(OOP_Project main.cpp
        Items/Item.cpp
        Items/Item.h
        Items/Potion.cpp
        Items/Potion.h
        Items/Armor.cpp
        Items/Armor.h)
