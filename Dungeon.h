#ifndef OOP_PROJECT_DUNGEON_H
#define OOP_PROJECT_DUNGEON_H
#include "Entity.h"
#include <iostream>
#include "Player.h"
using namespace std;


class Dungeon {
protected:
    const int id;
    inline static int idGenerator = 0;
    int level;
    Entity boss;
    int x;
    int y;
    bool unlocked;
    bool cleared;
public:
    Dungeon(int level = 1);
    Dungeon(int p_x, int p_y, bool p_unlocked, bool p_cleared, Entity p_boss, int level = 1);

    int getId() const;
    bool fight(Player &player);

    int getX() const;
    int getY() const;
    void setPosition(int x, int y);

    bool isUnlocked() const;
    void setUnlocked(bool unlocked);

    bool isCleared() const;
    void setCleared(bool cleared);

    const Entity& getBoss() const;
    void setBoss(const Entity& newBoss);
};


#endif //OOP_PROJECT_DUNGEON_H