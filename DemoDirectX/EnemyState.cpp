#include "EnemyState.h"


EnemyState::EnemyState(EnemyData *enemyData)
{
    this->enemyData = enemyData;
}

EnemyState::~EnemyState()
{

}

void EnemyState::update(float dt)
{

}

void EnemyState::handleKeyboard(std::map<int, bool> keys)
{

}

void EnemyState::onCollision(Entity *impactor)
{

}