#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerFallingState.h"
#include "GameDefine.h"

PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
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
        this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
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
            if (data.RegionCollision.right - data.RegionCollision.left <= Define::PLAYER_BOTTOM_RANGE_FALLING)
            {
                this->mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
            }
            break;
        case Entity::NotKnow:
            break;
        default:
            break;
    }
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
