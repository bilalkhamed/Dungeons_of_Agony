//
// Created by Bilal Hamed on 29/07/2026.
//

#include "Potion.h"
#include <stdexcept>
using namespace std;

const string Potion::possibleEffects[] = {"strength", "health", "resistance"};
const int Potion::possibleEffectsCount = size(Potion::possibleEffects);;
const double Potion::effectFactors[] = {3, 20, 0.7};
const double Potion::prices[] = {10, 5, 15};

Potion::Potion(string effect): Item("potion") {
    bool found = false;
    for (int i = 0; i < possibleEffectsCount; i++) {
        if (possibleEffects[i] == effect) {
            found = true;
        }
    }

    if (!found) {
        throw runtime_error("invalid potion type");
        return;
    }

    this->effect = effect;
}

double Potion::getEffectFactor(string effect) {
    int index = -1;
    for (int i = 0; i < possibleEffectsCount; i++) {
        if (possibleEffects[i] == effect) {
            index = i;
        }
    }

    return index == -1 ? 0 : effectFactors[index];
}

double Potion::getPrice() const {
    int index = -1;
    for (int i = 0; i < possibleEffectsCount; i++) {
        if (possibleEffects[i] == effect) {
            index = i;
        }
    }

    return index == -1 ? 0 : prices[index];
}

string Potion::getEffectType() const {
    return effect;
}
