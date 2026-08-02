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

public:
    Entity boss;
    int x;
    int y;
    bool isUnlocked;
    bool isCleared;
    Dungeon(int level = 1);
    Dungeon(int p_x, int p_y, bool p_unlocked, bool p_cleared, Entity p_boss, int level = 1);

    int getId() const;
    bool fight(Player &player);

};


#endif //OOP_PROJECT_DUNGEON_H
