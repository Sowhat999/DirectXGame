#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "GameLog.h"
#include "Sprite.h"
#include "MapReader\Tmx.h.in"
#include "GameConverter.h"
#include "Camera.h"
#include "GameGlobal.h"
#include "GameCollision.h"
#include "QuadTree.h"
#include "Brick.h"
#include "Enemy.h"

class GameMap
{
public:
    GameMap(char* filePath);
    void SetCamera(Camera* camera);
    void Update(float dt);
    void Draw();
    Tmx::Map* GetMap();
    RECT GetWorldMapBound();
    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();
    std::map<int, Sprite*> getListTileSet();

    bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
    bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
    bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    ~GameMap();

    std::vector<Enemy*> GetListEnemies();
    std::vector<Brick*> GetListBrick();
    QuadTree* GetQuadTree();

private:
    void LoadMap(char* filePath);

    Tmx::Map                        *mMap;
    std::map<int, Sprite*>          mListTileset;
    LPD3DXSPRITE                    mSpriteHandler;
    Camera                          *mCamera;
    QuadTree                        *mQuadTree;
    std::vector<Brick*>             mListBricks;
    std::vector<Enemy*>             mListEnemies;

    Sprite                          *mSpriteBricks, *mSpriteBrickGold;
};

#endif

