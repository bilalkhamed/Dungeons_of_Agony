#ifndef OOP_PROJECT_ENTITY_H
#define OOP_PROJECT_ENTITY_H
#include <iostream>
using namespace std;

class Entity {
protected:
    int hp;
    int damage;
    int attackSpeed;
public:
    Entity(int hp, int damage, int attackSpeed);

    int getHp() const;
    int getDamage() const;
    int getAttackSpeed() const;
};


#endif //OOP_PROJECT_ENTITY_H
