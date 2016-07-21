#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <map>

#include "Camera.h"
#include "GameGlobal.h"

class Entity
{

public:
    enum SideCollisions
    {
        Left,
        Right,
        Top,
        Bottom,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        NotKnow
    };

    struct CollisionReturn
    {
        bool IsCollided;
        RECT RegionCollision;
    };

    enum EntityTypes
    {
        Brick, Enemy, Mario, Static, BrickGoldNormal, BrickGoldEated
    };

    Entity();

    //ten cua Entity
    std::string name;

    //vi tri tam position x va y
    float posX, posY;

    //phan toc vx, vy
    float vx, vy;

    //size cua entity
    float width, height;

    int Tag; //Tag de nhan vien loai Entity

    virtual RECT GetBound();

    virtual void setPosition(float x, float y);

    virtual void setPosition(D3DXVECTOR2 pos);

    virtual void setPosition(D3DXVECTOR3 pos);

    virtual int getWidth();

    virtual int getHeight();

    virtual D3DXVECTOR3 GetPosition();

    virtual void update(float dt);

    //kiem soat viec va cham
    //khi xay ra va cham voi 1 thuc the nao do thi ham nay se dc goi de xu ly
    virtual void onCollision(Entity *impactor, CollisionReturn data, SideCollisions side);

    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    virtual void handleKeyboard(std::map<int, bool> keys);

protected:

};