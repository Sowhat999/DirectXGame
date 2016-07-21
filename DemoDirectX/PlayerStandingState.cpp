#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"

PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
    this->playerData = playerData;
    this->playerData->player->vx = 0;
    this->playerData->player->vy = 0;
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::update(float dt)
{

}

void PlayerStandingState::handleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        this->playerData->player->changeState(new PlayerRunningState(this->playerData), Player::PlayerStates::Running);
        return;
    }

    if (keys[VK_SPACE] && playerData->player->getState() != Player::Jumping 
        && playerData->player->getState() !=  Player::Falling)
    {
        this->playerData->player->changeState(new PlayerJumpingState(this->playerData), Player::Jumping);
        return;
    }
}

void PlayerStandingState::onCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    switch (side)
    {
        case Entity::Left:
            break;
        case Entity::Right:
            break;
        case Entity::Top:
            break;
        case Entity::TopLeft:
            break;
        case Entity::TopRight:
            break;
        case Entity::BottomLeft:
        case Entity::BottomRight:
        case Entity::Bottom:
            if (data.RegionCollision.right - data.RegionCollision.left <= PLAYER_BOTTOM_RANGE_FALLING)
            {
                this->playerData->player->changeState(new PlayerFallingState(playerData), Player::Falling);
            }
            break;
        case Entity::NotKnow:
            break;
        default:
            break;
    }
}