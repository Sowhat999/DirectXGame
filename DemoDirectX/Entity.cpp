#include "Entity.h"
#include "GameCollision.h"

Entity::Entity()
{
    Tag = 0;
}

D3DXVECTOR3 Entity::GetPosition()
{
    return D3DXVECTOR3(posX, posY, 0);
}

RECT Entity::GetBound()
{
    RECT bound;

    bound.left = posX - width / 2;
    bound.right = posX + width / 2;
    bound.top = posY - height / 2;
    bound.bottom = posY +height / 2;

    return bound;
}

void Entity::onCollision(Entity *impactor, CollisionReturn data, Entity::SideCollisions side)
{
    vx = 0, vy = 0;
}

void Entity::handleKeyboard(std::map<int, bool> keys)
{

}

void Entity::update(float dt)
{
    posX += vx;
    posY += vy;
}

void Entity::setPosition(float x, float y)
{
    setPosition(D3DXVECTOR2(x, y));
}

void Entity::setPosition(D3DXVECTOR2 pos)
{
    setPosition(D3DXVECTOR3(pos.x, pos.y, 0));
}

void Entity::setPosition(D3DXVECTOR3 pos)
{
    this->posX = pos.x;
    this->posY = pos.y; 
}

int Entity::getWidth()
{
    return width;
}

int Entity::getHeight()
{
    return height;
}