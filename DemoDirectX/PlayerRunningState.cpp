#include "PlayerRunningState.h"
#include "GameCollision.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "GameDefine.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    
    acceleratorX = 8.0f;

    this->mPlayerData->player->allowMoveLeft = true;
    this->mPlayerData->player->allowMoveRight = true;
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::update(float dt)
{

}

void PlayerRunningState::handleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        if (mPlayerData->player->allowMoveRight)
        {
            mPlayerData->player->SetReverse(false);

            //di chuyen sang phai
            if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->AddVx(acceleratorX);

                if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
                {
                    this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
                }
            }
        }
    }
    else if (keys[VK_LEFT])
    {
        if (mPlayerData->player->allowMoveLeft)
        {
            mPlayerData->player->SetReverse(true);

            //di chuyen sang trai
            if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->AddVx(-acceleratorX);

                if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
                {
                    this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
                }
            }
        }
    }
    else
    {
        this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        return;
    }
}

void PlayerRunningState::onCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

    switch (side)
    {
        case Entity::Left:
        {
            //va cham phia ben trai player
            if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
            {
                this->mPlayerData->player->allowMoveLeft = false;
                this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
                this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
            }

            return;
        }

        case Entity::Right: 
        {
            //va cham phia ben phai player
            if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
            {
                this->mPlayerData->player->allowMoveRight = false;
                this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
                this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
            }
            return;
        }

        case Entity::Top:
            break;

        case Entity::Bottom: case Entity::BottomLeft : case Entity::BottomRight:           
        {
            this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

            this->mPlayerData->player->SetVy(0);

            return;
        }
    }
}

PlayerState::StateName PlayerRunningState::GetState()
{
    return PlayerState::Running;
}
