#pragma once
#include "EnemyData.h"
#include "Entity.h"
#include <map>

class EnemyState
{
public:
    EnemyState(EnemyData *enemyData);
    ~EnemyState();

    virtual void update(float dt);

    virtual void handleKeyboard(std::map<int, bool> keys);

    virtual void onCollision(Entity *impactor);

protected:
    EnemyData *enemyData;
};

