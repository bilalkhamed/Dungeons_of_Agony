#ifndef OOP_PROJECT_PLAYER_H
#define OOP_PROJECT_PLAYER_H
#include <iostream>
#include "Entity.h"
#include "Items/Potion.h"
using namespace std;

class Player : public Entity {
protected:
    double gold = 0;
    int armor;
    float goldRatio = 1;
    Potion *storage;
    int storageCapacity = 10;
    int currentSize = 0;
public:
    Player(int hp, int damage, int attackSpeed, int armor = 0);
    ~Player();

    bool addPotion(Potion p);
    int getHealthPotions() const;
    int getResistancePotions() const;
    int getStrengthPotions() const;
    void removePotion(string type);
    void increaseGold(int amount);
    void decreaseGold(int amount);
    void increaseCapacity();
    void increaseAttackSpeed();
    void setHp(int hp);

    double getGold() const;
    int getArmor() const;
    float getGoldRatio() const;
};


#endif //OOP_PROJECT_PLAYER_H
