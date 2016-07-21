#include "PlayerJumpingState.h"
#include "GameCollision.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
    this->playerData = playerData;    
    this->playerData->player->vy = PLAYER_MIN_JUMP_VELOCITY;

    acceleratorY = 0.2;
    acceleratorX = 0.06f;
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::update(float dt)
{
    this->playerData->player->vy += acceleratorY;   

    if (playerData->player->vy >= 0)
    {
        playerData->player->changeState(new PlayerFallingState(this->playerData), Player::Falling);

        return;
    }

    if (playerData->player->getMoveDirection() == Player::MoveToLeft)
    {
        //player dang di chuyen sang ben trai        

        if (playerData->player->vx < 0)
        {
            this->playerData->player->vx += acceleratorX;

            //doi state
            if (playerData->player->vx > 0)
            {
                playerData->player->vx = 0;
            }            
        }
    }
    else
    {
        //player dang di chuyen sang phai       
        if (playerData->player->vx > 0)
        {
            this->playerData->player->vx -= acceleratorX;

            //doi state
            if (playerData->player->vx < 0)
            {
                playerData->player->vx = 0;
            }                
        }
    }
}

void PlayerJumpingState::handleKeyboard(std::map<int, bool> keys)
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
        //this->playerData->player->vx = 0;
    }
}

void PlayerJumpingState::onCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
 {
    switch (side)
    {
    case Entity::Left: case Entity::TopLeft: case Entity::BottomLeft:
            if (playerData->player->getMoveDirection() == Player::MoveToLeft)
            {
                this->playerData->player->vy = 0;
                this->playerData->player->posY += (data.RegionCollision.bottom - data.RegionCollision.top);
                this->playerData->player->posX += (data.RegionCollision.right - data.RegionCollision.left);
                this->playerData->player->changeState(new PlayerFallingState(this->playerData), Player::Falling);
            }

            return;

    case Entity::Right: case Entity::TopRight: case Entity::BottomRight:
            if (playerData->player->getMoveDirection() == Player::MoveToRight)
            {
                this->playerData->player->vy = 0;
                this->playerData->player->posY += (data.RegionCollision.bottom - data.RegionCollision.top);
                this->playerData->player->posX -= (data.RegionCollision.right - data.RegionCollision.left);
                this->playerData->player->changeState(new PlayerFallingState(this->playerData), Player::Falling);
            }
            return;

        case Entity::Top:
            this->playerData->player->vy = 0;
            this->playerData->player->posY += (data.RegionCollision.bottom - data.RegionCollision.top);
            this->playerData->player->changeState(new PlayerFallingState(this->playerData), Player::Falling);
            return;

        case Entity::Bottom:
            //this->playerData->player->changeState(new PlayerStandingState(this->playerData), Player::Standing);
            return;

        default:
            break;
    }
}