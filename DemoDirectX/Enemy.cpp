#include "Enemy.h"


Enemy::Enemy()
{
    this->enemyData = new EnemyData();
    this->enemyData->enemy = this;
    this->enemyData->state = nullptr;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
    Animation::Update(dt);

    if (this->enemyData->state)
    {
        this->enemyData->state->update(dt);
    }
    
}

void Enemy::handleKeyboard(std::map<int, bool> keys)
{
    if (this->enemyData->state)
    {
        this->enemyData->state->handleKeyboard(keys);
    }
}

void Enemy::setCamera(Camera *camera)
{
    this->mCamera = camera;
}

void Enemy::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    if (mCamera)
    {
        D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
                                        GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

        Animation::Draw(position, sourceRect, scale, trans, angle, rotationCenter, colorKey);
    }
    else
        Animation::Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Enemy::SetGravity(D3DXVECTOR3 gravity)
{
    mGravity = gravity;
}

void Enemy::changeState(EnemyState *newState)
{
    delete this->enemyData->state;

    this->enemyData->state = newState;
}