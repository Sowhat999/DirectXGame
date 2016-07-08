#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <map>

#include "Camera.h"
#include "GameCollision.h"
#include "GameGlobal.h"

class Entity
{

public:

    enum EntityTypes
    {
        Brick, Enemy, Mario, Static, BrickGoldNormal, BrickGoldEated
    };

    Entity();

    RECT Bound;
    //vi tri tam

    virtual D3DXVECTOR3 GetEntityPosition();
    int Tag; //Tag de nhan vien loai Entity

    virtual RECT GetBoundOnScreen(Camera *camera);

    //kiem soat viec va cham
    //khi xay ra va cham voi 1 thuc the nao do thi ham nay se dc goi de xu ly
    virtual void onCollision(Entity *impactor);

    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    virtual void hanleInput(std::map<int, bool> keyCodes);

    //tra ve ket qua cua viec xu ly va cham co bien bool la IsCollide = true neu xay ra va cham va nguoc lai
    GameCollision::CollisionReturn CollisionResult;    

protected:

};