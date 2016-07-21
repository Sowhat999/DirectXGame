#include "PlayerRunningState.h"
#include "GameCollision.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
    this->playerData = playerData;
    
    acceleratorX = 0.06f;
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
        //di chuyen sang phai
        if (this->playerData->player->vx < PLAYER_MAX_RUNNING_SPEED)
        {
            this->playerData->player->vx += acceleratorX;

            if (this->playerData->player->vx >= PLAYER_MAX_RUNNING_SPEED)
            {
                this->playerData->player->vx = PLAYER_MAX_RUNNING_SPEED;
            }
        }
    }
    else if (keys[VK_LEFT])
    {
       //di chuyen sang trai
        if (this->playerData->player->vx > -PLAYER_MAX_RUNNING_SPEED)
        {
            this->playerData->player->vx -= acceleratorX;

            if (this->playerData->player->vx <= -PLAYER_MAX_RUNNING_SPEED)
            {
                this->playerData->player->vx = -PLAYER_MAX_RUNNING_SPEED;
            }
        }
    }
    else
    {
        this->playerData->player->changeState(new PlayerStandingState(this->playerData), Player::Standing);
        return;
    }

    if (keys[VK_SPACE] && playerData->player->getState() != Player::Jumping 
        && playerData->player->getState() != Player::Falling)
    {
        this->playerData->player->changeState(new PlayerJumpingState(this->playerData), Player::Jumping);
    }
}

void PlayerRunningState::onCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->playerData->player, data);

    switch (side)
    {
        case Entity::Left:
            //va cham phia ben trai player
            if (this->playerData->player->getMoveDirection() == Player::MoveToLeft)
            {
                this->playerData->player->posX += (data.RegionCollision.right - data.RegionCollision.left);
                this->playerData->player->changeState(new PlayerStandingState(this->playerData), Player::Standing);
            }
            
            return;

        case Entity::Right: 
            //va cham phia ben phai player
            if (this->playerData->player->getMoveDirection() == Player::MoveToRight)
            {
                this->playerData->player->posX -= (data.RegionCollision.right - data.RegionCollision.left);
                this->playerData->player->changeState(new PlayerStandingState(this->playerData), Player::Standing);
            }
            return;

        case Entity::Top:
            break;

        case Entity::Bottom: case Entity::BottomLeft : case Entity::BottomRight:            
            this->playerData->player->vy = 0;
            this->playerData->player->posY -= (data.RegionCollision.bottom - data.RegionCollision.top);

            if (data.RegionCollision.right - data.RegionCollision.left <= PLAYER_BOTTOM_RANGE_FALLING)
            {
                this->playerData->player->changeState(new PlayerFallingState(playerData), Player::Falling);
            }

            return;
    }
}