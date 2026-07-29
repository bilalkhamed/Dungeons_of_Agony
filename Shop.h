#ifndef SHOP_H
#define SHOP_H

#include "Item.h"

class Shop {
private:
    // Data members
    Item inventory[7];

public:
    // Methods
    void upgradeAttackSpeed();
    void upgradeWeapon();
    void upgradeInventory();
    void buyItem(int itemId);
    void displayInventory();
};

#endif // SHOP_H