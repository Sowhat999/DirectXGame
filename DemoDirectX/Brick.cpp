#include "Brick.h"


Brick::Brick(RECT rectBound, RECT *sourceRect, D3DXVECTOR3 position)
{
    SourceRect = sourceRect;
    posX = position.x;
    posY = position.y;
    width = (rectBound.right - rectBound.left);
    height = (rectBound.bottom - rectBound.top);
}

Brick::~Brick()
{
}

//RECT Brick::getRealBound()
//{
//    //position ve o vi tri chinh giua
//    RECT bound;
//    bound.left = Position.x - (Bound.left - Bound.right) / 2;
//    bound.right = bound.left + (Bound.left - Bound.right);
//    bound.top = Position.y - (Bound.bottom - Bound.top) / 2;
//    bound.bottom = bound.top + (Bound.bottom - Bound.top);
//
//    return bound;
//}

//
//RECT Brick::getBoundOnScreen(Camera *camera)
//{
//    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - camera->GetPosition().x, 
//                                    GameGlobal::GetHeight() / 2 - camera->GetPosition().y);
//
//    RECT bound;
//    bound.left = Position.x - (Bound.left - Bound.right) / 2 + trans.x;
//    bound.right = bound.left + (Bound.left - Bound.right);
//    bound.top = Position.y - (Bound.bottom - Bound.top) / 2 + trans.y;
//    bound.bottom = bound.top + (Bound.bottom - Bound.top);
//
//    return bound;
//}