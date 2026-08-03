#include "Dungeon.h"
#include <iostream>
using namespace std;

Dungeon::Dungeon(int level): level(level),x(0), y(0), unlocked(false), cleared(false), boss(200, 10, 1), id(++idGenerator) {

    switch (level) {
        case 1:
            boss.setMaxHp(200);
            boss.setDamage(10);
            break;
        case 2:
            boss.setMaxHp(300);
            boss.setDamage(14);
            break;
        case 3:
            boss.setMaxHp(400);
            boss.setDamage(20);
    }
}

Dungeon::Dungeon(int p_x, int p_y, bool p_unlocked, bool p_cleared, Entity p_boss, int level):
        id(++idGenerator),
        x(p_x),
        y(p_y),
        unlocked(p_unlocked),
        cleared(p_cleared),
        boss(p_boss),
        level(level){};

int Dungeon::getX() const {return x;}
int Dungeon::getY() const{return y;}

void Dungeon::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Dungeon::isUnlocked() const {return unlocked;}

void Dungeon::setUnlocked(bool unlocked) {
    this->unlocked = unlocked;
}

bool Dungeon::isCleared() const{return cleared;}

void Dungeon::setCleared(bool cleared) {
    this->cleared = cleared;
}

const Entity& Dungeon::getBoss() const{return boss;}

void Dungeon::setBoss(const Entity& newBoss) {
    this->boss = newBoss;
}

bool Dungeon::fight(Player &player) {
    int playerAttackSpeed = player.getAttackSpeed();
    int playerHp = player.getHp();
    int playerArmor = player.getArmor();
    int playerDamage = player.getDamage();
    int bossHp = boss.getHp();
    int bossDamage = boss.getDamage();

    int healthPotionsCount = player.getHealthPotions();
    int strengthPotionsCount = player.getStrengthPotions();
    int resistancePotionsCount = player.getResistancePotions();

    if (strengthPotionsCount > 0) {
        playerDamage += Potion::getEffectFactor("strength");
    }
    if (resistancePotionsCount > 0) {
        playerArmor += (playerArmor*Potion::getEffectFactor("resistance"));
    }
    player.removePotion("strength");
    player.removePotion("resistance");

    float bossWin = (float) (playerHp+playerArmor)/bossDamage;
    float playerWin = (float) (bossHp)/((playerDamage)*playerAttackSpeed);

    float difference = bossWin - playerWin;
    int hpAfterFight = difference*bossDamage;

    if (playerWin < bossWin) {
        player.setHp(hpAfterFight);
        return true;
    }


    int usedPotions = 0;
    while (hpAfterFight <= 0 && usedPotions <= healthPotionsCount) {
        hpAfterFight += Potion::getEffectFactor("health");
        usedPotions++;
    }

    if (hpAfterFight > 0) {
        for (int i = 0; i<usedPotions; i++) {
            player.removePotion("health");
        }
        player.setHp(hpAfterFight);
        return true;
    }

    return false;
}

int Dungeon::getId() const {
    return id;
}