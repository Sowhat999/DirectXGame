#include "GameDebugDraw.h"


GameDebugDraw::GameDebugDraw()
{
    mSpriteHandler = GameGlobal::GetCurrentSpriteHandler();
    mSpriteHandler->GetDevice(&mddv);
    D3DXCreateLine(mddv, &LineDraw);
    LineDraw->SetWidth(5);
    mColor = D3DCOLOR_XRGB(71, 85, 119);
    
}

GameDebugDraw::~GameDebugDraw()
{
    
}

void GameDebugDraw::Draw()
{

}

void GameDebugDraw::setLineSize(float width)
{
    LineDraw->SetWidth(width);
}

void GameDebugDraw::DrawLine(D3DXVECTOR2 lines[], int count)
{
    LineDraw->Begin();
    LineDraw->Draw(lines, count, mColor);
    LineDraw->End();
}

void GameDebugDraw::DrawRect(RECT rect, Camera *camera)
 {

    D3DXVECTOR3 trans = D3DXVECTOR3(0, 0, 0);

    if (camera)
    {
        trans = D3DXVECTOR3(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2, 0) - camera->GetPosition();
    }    

    D3DXVECTOR2 lines[] = { D3DXVECTOR2(rect.left + trans.x, rect.top + trans.y),
                            D3DXVECTOR2(rect.right + trans.x, rect.top + trans.y), 
                            D3DXVECTOR2(rect.right + trans.x, rect.bottom + trans.y), 
                            D3DXVECTOR2(rect.left + trans.x, rect.bottom + trans.y), 
                            D3DXVECTOR2(rect.left + trans.x, rect.top + trans.y) };

    DrawLine(lines, 5);
}

void GameDebugDraw::setColor(D3DCOLOR color)
{
    mColor = color;
}