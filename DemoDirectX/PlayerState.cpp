#include "PlayerState.h"


PlayerState::PlayerState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
}

PlayerState::PlayerState()
{

}

PlayerState::~PlayerState()
{
}

void PlayerState::update(float dt)
{

}

void PlayerState::handleKeyboard(std::map<int, bool> keys)
{

}

void PlayerState::onCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}