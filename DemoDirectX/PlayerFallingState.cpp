#include "PlayerFallingState.h"
#include "Player.h"
#include "GameCollision.h"
#include "PlayerStandingState.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
    this->playerData = playerData;
    acceleratorY = 0.2f;
    acceleratorX = 0.1f;

    if (this->playerData->player->vx == 0)
    {
        allowMoveX = false;
    }
    else
    {
        allowMoveX = true;
    }
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::update(float dt)
{
    this->playerData->player->vy += acceleratorY;

    if (playerData->player->vy >= PLAYER_MAX_JUMP_VELOCITY)
    {
        playerData->player->vy = PLAYER_MAX_JUMP_VELOCITY;
    }
}

void PlayerFallingState::handleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        isLeftOrRightKeyPressed = true;
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
        isLeftOrRightKeyPressed = true;
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
        isLeftOrRightKeyPressed = false;        
    }
}

void PlayerFallingState::onCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->playerData->player, data);

    switch (side)
    {
        case Entity::Left:
            if (playerData->player->getMoveDirection() == Player::MoveToLeft)
            {
                this->playerData->player->posX += (data.RegionCollision.right - data.RegionCollision.left);
                this->playerData->player->vx = 0;
            }
            break;

        case Entity::Right:
            if (playerData->player->getMoveDirection() == Player::MoveToRight)
            {
                this->playerData->player->posX -= (data.RegionCollision.right - data.RegionCollision.left);
                this->playerData->player->vx = 0;
            }
            break;

        case Entity::Top:
            break;

        case Entity::Bottom:
        case Entity::BottomRight:
        case Entity::BottomLeft:
            if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
            {
                this->playerData->player->posY -= (data.RegionCollision.bottom - data.RegionCollision.top);

                if (isLeftOrRightKeyPressed)
                {
                    this->playerData->player->changeState(new PlayerRunningState(this->playerData), Player::Running);
                }
                else
                {
                    this->playerData->player->changeState(new PlayerStandingState(this->playerData), Player::Standing);
                }
            }
            return;

        default:
            break;
    }
}