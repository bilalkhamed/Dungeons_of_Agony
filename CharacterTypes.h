#ifndef OOP_PROJECT_CHARACTERTYPES_H
#define OOP_PROJECT_CHARACTERTYPES_H
#include <iostream>

#include "Player.h"
using namespace std;

// Warrior header

class Warrior : public Player {
protected:
public:
    Warrior(int hp = 150, int damage = 10, int attackSpeed = 1);
};

// Mage header

class Mage : public Player {
public:
    Mage(int hp = 50, int damage = 20, int attackSpeed = 1);
};

// Assassin header

class Assassin : public Player {
protected:
public:
    Assassin(int hp = 100, int damage = 15, int attackSpeed = 2);
};

#endif //OOP_PROJECT_CHARACTERTYPES_H
