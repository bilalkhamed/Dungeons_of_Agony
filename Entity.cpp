#include "Entity.h"

Entity::Entity(int hp, int damage, int attackSpeed) : hp(hp), damage(damage), attackSpeed(attackSpeed){

}

int Entity::getHp() const {
    return hp;
}

int Entity::getDamage() const {
    return damage;
}

int Entity::getAttackSpeed() const {
    return attackSpeed;
}

int Entity::getMaxHp() const {
    return maxHp;
}

int Entity::setMaxHp(int maxHp) {
    this->maxHp = maxHp;
    this->hp = maxHp;
}

int Entity::setDamage(int damage) {
    this->damage = damage;
}

int Entity::setAttackSpeed(int attackSpeed) {
    this->attackSpeed = attackSpeed;
}
