#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
    PlayerJumpingState(PlayerData *playerData);
    ~PlayerJumpingState();

    void update(float dt);

    void handleKeyboard(std::map<int, bool> keys);

    void onCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
    float acceleratorY;
    float acceleratorX;
};

