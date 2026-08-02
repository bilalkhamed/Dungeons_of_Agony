//
// Created by Bilal Hamed on 29/07/2026.
//

#include "Armor.h"
#include <stdexcept>
using namespace std;

const double Armor::armorBoost[] = {25, 50, 80, 150};
const string Armor::possibleMaterials[] = {"chain", "iron", "diamond", "dragon scale"};
const int Armor::possibleMaterialsCount = size(Armor::possibleMaterials);
const double Armor::prices[] = {10, 18, 30, 150};

Armor::Armor(string material): Item("armor") {
    bool found = false;
    for (int i = 0; i < possibleMaterialsCount; i++) {
        if (possibleMaterials[i] == material) {
            found = true;
        }
    }

    if (!found) {
        throw runtime_error("invalid potion type");
        return;
    }

    this->material = material;
}

double Armor::getBoost() const {
    int index = -1;
    for (int i = 0; i < possibleMaterialsCount; i++) {
        if (possibleMaterials[i] == material) {
            index = i;
        }
    }

    return index == -1 ? 0 : armorBoost[index];
}

double Armor::getPrice() const {
    int index = -1;
    for (int i = 0; i < possibleMaterialsCount; i++) {
        if (possibleMaterials[i] == material) {
            index = i;
        }
    }

    return index == -1 ? 0 : prices[index];
}

