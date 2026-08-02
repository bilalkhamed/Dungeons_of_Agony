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

void Entity::setMaxHp(int maxHp) {
    this->maxHp = maxHp;
    this->hp = maxHp;
}

void Entity::setDamage(int damage) {
    this->damage = damage;
}

void Entity::setAttackSpeed(int attackSpeed) {
    this->attackSpeed = attackSpeed;
}
