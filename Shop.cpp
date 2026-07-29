#include "Shop.h"
#include <iostream>
using namespace std;

void Shop::upgradeAttackSpeed(Player& p) {
    p.increaseAttackSpeed();
}

void Shop::upgradeWeapon(Player& p) {
      p.increaseDamage
 }

void Shop::upgradeInventory() {
    
}

void Shop::buyItem(Player& p, int itemId) {
    if (p.getGold() - inventory[itemId - 1].getPrice() >= 0) {
        if (p.addPotion(inventory[itemId - 1])) {
            p.decreaseGold(inventory[itemId - 1].getprice());
        }
    }
    else {
        cout << "Not enough gold to buy item!" << endl;
    }
}

void Shop::displayInventory() {
    cout << "================================" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Item #" << i + 1 << "\t - \t";
    }
    cout << endl;
    for (int i = 0; i < 7; i++) {
        cout << inventory[i] << "\t - \t";
    }
    cout << endl;
    for (int i = 0; i < 7; i++) {
        cout << inventory[i].getPrice() << "\t - \t";
    }
    cout << endl;
}
