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

bool Player::addPotion(Potion &p) {
    if (storageCapacity == currentSize) {
        cout << "The storage is full, you cant add items." << endl;
        return false;
    }

    storage[currentSize] = p;
    currentSize++;
    return true;
}

void Player::removePotion(int index) {
    index--;
    for (int i = index; i<currentSize-1; i++) {
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

double Player::getGold() const{
    return gold;
}

int Player::getArmor() const {
    return armor;
}

float Player::getGoldRatio() const {
    return goldRatio;
}
