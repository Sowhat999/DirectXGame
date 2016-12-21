#ifndef __GAME_OBJECT_BRICK_GOLD__
#define __GAME_OBJECT_BRICK_GOLD__
#include "QuadTree.h"
#include "Sprite.h"
#include "GameGlobal.h"
#include "Camera.h"
#include "Brick.h"

class BrickGold : public Brick
{
public:
    BrickGold(D3DXVECTOR3 position);
    ~BrickGold();

    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();
};

#endif