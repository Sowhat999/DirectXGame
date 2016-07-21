#include "Player.h"
#include "PlayerFallingState.h"
#include "GameCollision.h"

Player::Player()
{
    animationStanding = new Animation("mario/standingright.png", 1, 1, 1, 0);
    animationJumping = new Animation("mario/jumpingright.png", 1, 1, 1, 0);
    animationRunning = new Animation("mario/runningright.png", 2, 1, 2, 0.15f);

    this->playerData = new PlayerData();
    this->playerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->changeState(new PlayerFallingState(this->playerData), PlayerStates::Falling);
}

Player::~Player()
{
}

void Player::update(float dt)
{    
    Entity::update(dt);

    currentAnimation->Update(dt);

    if (this->playerData->state)
    {
        this->playerData->state->update(dt);
    }   

    string s;
    switch (currentState)
    {
        case Player::Standing:
            s = "standing";
            break;
        case Player::Running:
            s = "running";
            break;
        case Player::Falling:
            s = "falling";
            break;
        case Player::Jumping:
            s = "jumping";
            break;
        case Player::Die:
            break;
        default:
            break;
    }
    GAMELOG("current State: %s", s.c_str());
}

void Player::handleKeyboard(std::map<int, bool> keys)
{
    if (this->playerData->state)
    {
        this->playerData->state->handleKeyboard(keys);
    }
}

void Player::setCamera(Camera *camera)
{
    this->mCamera = camera;
}

void Player::Draw(D3DXVECTOR3 position, RECT *sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXVECTOR2 scalingCenter, D3DXCOLOR colorKey)
{
    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
                                        GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

    if (mCamera)
    {
        currentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, scalingCenter, colorKey);
    }
    else
    {
        currentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, scalingCenter, colorKey);
    }        
}

void Player::changeState(PlayerState *newState, Player::PlayerStates stateName)
{
    delete this->playerData->state;

    this->playerData->state = newState;

    this->changeAnimation(stateName);

    currentState = stateName;
}

void Player::onCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    this->playerData->state->onCollision(impactor, side, data);
}

RECT Player::GetBound()
{
    RECT rect;
    rect.left = this->posX - currentAnimation->getWidth() / 2;
    rect.right = rect.left + currentAnimation->getWidth();
    rect.top = this->posY - currentAnimation->getHeight() / 2;
    rect.bottom = rect.top + currentAnimation->getHeight();

    return rect;
}

void Player::changeAnimation(PlayerStates state)
{
    switch (state)
    {
        case Player::Running:
            currentAnimation = animationRunning;
            break;

        case Player::Standing:
            currentAnimation = animationStanding;
            break;

        case Player::Falling:
            currentAnimation = animationJumping;
            break;

        case Player::Jumping:
            currentAnimation = animationJumping;
            break;

        default:
            break;
    }

    this->width = currentAnimation->getWidth();
    this->height = currentAnimation->getHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
    if (this->vx > 0)
    {
        return MoveDirection::MoveToRight;
    }
    else if (this->vx < 0)
    {
        return MoveDirection::MoveToLeft;
    }

    return MoveDirection::None;
}

void Player::onNoCollisionWithBottom()
{
    if (currentState != Jumping && currentState != Falling)
    {
        this->changeState(new PlayerFallingState(this->playerData), Player::Falling);
    }    
}

Player::PlayerStates Player::getState()
{
    return currentState;
}