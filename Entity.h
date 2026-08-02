#ifndef OOP_PROJECT_ENTITY_H
#define OOP_PROJECT_ENTITY_H
#include <iostream>
using namespace std;

class Entity {
protected:
    int hp;
    int damage;
    int attackSpeed;
    int maxHp;
public:
    Entity(int hp, int damage, int attackSpeed);

    int getHp() const;
    int getDamage() const;
    int getAttackSpeed() const;
    int getMaxHp() const;

    void setMaxHp(int maxHp);
    void setDamage(int damage);
    void setAttackSpeed(int attackSpeed);
};


#endif //OOP_PROJECT_ENTITY_H
