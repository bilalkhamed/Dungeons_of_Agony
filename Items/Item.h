//
// Created by Bilal Hamed on 29/07/2026.
//

#ifndef OOP_PROJECT_ITEM_H
#define OOP_PROJECT_ITEM_H

#include <string>
using namespace std;

class Item {
protected:
    string type;
    double price;
    const static string possibleTypes[];
    const static int possibleTypesCount;
public:
    Item(string type);
    virtual double getPrice() const = 0;
};




#endif //OOP_PROJECT_ITEM_H
