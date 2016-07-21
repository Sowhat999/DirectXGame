#pragma once
#include "PlayerData.h"
#include "Entity.h"
#include "GameCollision.h"
#include <map>

class PlayerState
{
public:
    ~PlayerState();

    virtual void update(float dt);

    virtual void handleKeyboard(std::map<int, bool> keys);

    //side va cham voi player
    virtual void onCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
    PlayerState(PlayerData *playerData);
    PlayerState();
    

    PlayerData *playerData;
};

