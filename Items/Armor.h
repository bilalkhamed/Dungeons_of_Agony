//
// Created by Bilal Hamed on 29/07/2026.
//

#ifndef OOP_PROJECT_ARMOR_H
#define OOP_PROJECT_ARMOR_H
#include "Item.h"


class Armor: public Item {
private:
    string material;
    const static string possibleMaterials[];
    const static int possibleMaterialsCount;
    const static double armorBoost[];
    const static double prices[];

public:
    Armor(string material);
    double getBoost() const;
    double getPrice() const override;
};


#endif //OOP_PROJECT_ARMOR_H
