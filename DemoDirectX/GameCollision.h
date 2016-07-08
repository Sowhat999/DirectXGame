#pragma once
#ifndef __GAME_COLLISION__
#define __GAME_COLLISION__

#include <d3dx9.h>
#include <d3d9.h>
#include "GameLog.h"

class GameCollision
{
public:
    struct CollisionReturn
    {
        bool IsCollided;
        RECT RegionCollision;
    };

    GameCollision();
    //kiem tra va cham giua 2 hinh chu nhat
    static CollisionReturn RectangleAndRectangle(RECT rect, RECT rect2);

    //kiem tra 1 diem co nam trong hinh chu nhat hay khong
    static bool PointAndRectangle(float x, float y, RECT rect);

    //hinh chu nhat va hinh tron
    static bool RectangleAndCircle(RECT rect, int circlex, int circley, int circleRadius);
    ~GameCollision();
};

#endif
