#pragma once
#ifndef __GAME_OBJECT_BRICK__
#define __GAME_OBJECT_BRICK__

#include "QuadTree.h"
#include "Sprite.h"
#include "GameGlobal.h"
#include "Camera.h"
#include "Animation.h"

//vien gach
class Brick : public Animation
{
public:
    ~Brick();

protected:
    Brick();

    bool init(D3DXVECTOR3 position);
    virtual const char* FileName() = 0; // bat buoc phai override ham nay
    virtual int TotalFrame() = 0; //so frame cua animation
    virtual int Row() = 0; // so row cua resource hinh anh animation
    virtual int Column() = 0; // so cot cua resource hinh anh animation
    virtual float SecondPerFrame() = 0; //so giay de chuyen frame cua animation
};

#endif
