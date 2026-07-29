#include "CharacterTypes.h"
#include <iostream>
using namespace std;


// Warrior implementation

Warrior:: Warrior(int hp, int damage, int attackSpeed): Player(hp, damage, attackSpeed, 5) {};

// Mage implementation

Mage:: Mage(int hp, int damage, int attackSpeed): Player(hp, damage, attackSpeed) {};

// Assassin implementation

Assassin::Assassin(int hp, int damage, int attackSpeed): Player(hp,damage, attackSpeed) {};
