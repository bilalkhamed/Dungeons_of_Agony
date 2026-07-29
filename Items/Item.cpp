//
// Created by Bilal Hamed on 29/07/2026.
//

#include "Item.h"
#include <iostream>


Item::Item(string type) {
    bool found = false;
    for (int i = 0; i < possibleTypesCount; i++) {
        if (possibleTypes[i] == type) {
            found = true;
        }
    }

    if (!found) {
        throw runtime_error("invalid item type");
        return;
    }

    this->type = type;
}

const string Item::possibleTypes[] = {"potion", "armor"};
const int Item::possibleTypesCount = size(Item::possibleTypes);