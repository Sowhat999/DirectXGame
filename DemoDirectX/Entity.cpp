#include "Entity.h"


Entity::Entity()
{
    Tag = 0;
}

D3DXVECTOR3 Entity::GetEntityPosition()
{
    return D3DXVECTOR3(Bound.left, Bound.top, 0);
}

RECT Entity::GetBoundOnScreen(Camera *camera)
{
    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - camera->GetPosition().x,
        GameGlobal::GetHeight() / 2 - camera->GetPosition().y);

    RECT bound;
    bound.left = Bound.left + trans.x;
    bound.right = bound.left + (Bound.right - Bound.left);
    bound.top = Bound.top + trans.y;
    bound.bottom = bound.top + (Bound.bottom - Bound.top);

    return bound;
}

void Entity::onCollision(Entity *impactor)
{

}

void Entity::hanleInput(std::map<int, bool> keyCodes)
{

}