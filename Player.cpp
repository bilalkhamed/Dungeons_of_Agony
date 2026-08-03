#include "Player.h"
#include<iostream>
#include "Items/Potion.h"
using namespace std;

Player::Player(int hp, int damage, int attackSpeed, int armor) : Entity(hp, damage, attackSpeed), armor(armor) {
    storage = new Potion[storageCapacity];
}

Player::~Player() {
    delete []storage;
}

void Player::setGold(double gold) {
    this->gold = gold;
}

bool Player::addPotion(Potion p) {
    if (storageCapacity == currentSize) {
        cout << "The storage is full, you cant add items." << endl;
        return false;
    }

    storage[currentSize] = p;
    currentSize++;
    return true;
}

int Player::getHealthPotions() const {
    int count = 0;
    for (int i =0; i<currentSize; i++) {
        if (storage[i].getEffectType() == "health") count++;
    }
    return count;
}

int Player::getStrengthPotions() const {
    int count = 0;
    for (int i =0; i<currentSize; i++) {
        if (storage[i].getEffectType() == "strength") count++;
    }
    return count;
}

int Player::getResistancePotions() const {
    int count = 0;
    for (int i =0; i<currentSize; i++) {
        if (storage[i].getEffectType() == "resistance") count++;
    }
    return count;
}

void Player::removePotion(string type) {
    int foundIndex = -1;
    for (int i = 0; i < currentSize; i++) {
        if (storage[i].getEffectType() == type) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        return;
    }

    for (int i = foundIndex; i < currentSize - 1; i++) {
        storage[i] = storage[i+1];
    }
    currentSize--;
}

void Player::increaseGold(int amount) {
    if (amount > 0) gold += amount;
}

void Player::decreaseGold(int amount) {
    if (amount > 0) gold -= amount;
}

void Player::increaseCapacity() {
    storageCapacity+=5;
}

void Player::increaseAttackSpeed() {
    attackSpeed += 1;
}

void Player::increaseArmor(int amount) {
    if (amount > 0) armor += amount;
}

void Player::setHp(int hp) {
    this->hp = hp;
}

double Player::getGold() const{
    return gold;
}

int Player::getArmor() const {
    return armor;
}

float Player::getGoldRatio() const {
    return goldRatio;
}