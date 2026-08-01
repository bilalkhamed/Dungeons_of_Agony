//
// Created by Bilal Hamed on 29/07/2026.
//

#ifndef OOP_PROJECT_POTION_H
#define OOP_PROJECT_POTION_H
#include "Item.h"

class Potion: public Item {
private:
    string effect;
    static const string possibleEffects[];
    static const double effectFactors[];
    static const int possibleEffectsCount;
    const static double prices[];

public:
    Potion() : Item("potion") {};
    Potion(string effect);
    double getEffectFactor() const;
    double getPrice() const override;
};


#endif //OOP_PROJECT_POTION_H
