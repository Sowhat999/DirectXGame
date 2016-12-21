//#ifndef __GAME_SCENES__
//#define __GAME_SCENES__
//
//#include <d3dx9.h>
//#include <d3d9.h>
//
//#include "QuadTree.h"
//#include "Brick.h"
//#include "BrickGold.h"
//#include "Enemy.h"
//#include "GameMap.h"
//#include "Scene.h"
//#include "EnemyMushRoom.h"
//#include "GameDebugDraw.h"
//#include "Player.h"
//
//#define TIME_KEY_HOLDING 0.12f //thoi gian tinh la key dang duoc giu
//
//class GameScene
//{
//public:
//    GameScene(char *mapFilePath);
//    ~GameScene();
//
//    void Update(float dt);
//    void Draw();
//    void LoadContent();
//    void SetCamera(Camera *camera);
//    Camera* GetCamera();
//
//    std::vector<Enemy*> GetListEnemies();
//    std::vector<Brick*> GetListBrick();
//    std::vector<Brick*> GetListBrickGold();
//
//    void OnKeyDown(int keyCode);
//    void OnKeyUp(int keyCode);
//
//    GameMap *GetMap();
//
//protected:
//    void LoadMapData();
//    void HandleInput(float dt);
//
//    bool IsKeyPress(int keyCode);
//
//    void CheckCameraAndWorldMap(); //kiem tra su va cham cua camera va cac duong bien cua worldmap
//
//    //kiem tra va cham cac vat the trong game
//    void checkCollision();
//
//    void drawQuadTree(QuadTree *quadtree);
//
//    GameMap *mGameMap;
//    Camera  *mCamera;
//    GameDebugDraw           *mGameDebugDraw;
//    D3DXVECTOR3             mGravity; //trong luc game
//
//    //thoi gian giu phim
//    float                   mTimeArrowLeftHolding,
//                            mTimeArrowRightHolding,
//                            mTimeSpaceHolding;
//
//    std::vector<Brick*>     mListBrick, 
//                            mListBrickGold;
//
//    std::vector<Enemy*>     mListEnemies;
//
//    QuadTree                *mQuadTree;
//    Sprite                  *mSpriteBricks, *mSpriteBrickGold;
//    char                    *mMapPath;
//    std::vector<Entity*>    mListCollisionAble;
//
//    std::map<int, bool>     mKeyCodes;
//    
//    Player                  *player;
//};
//
//#endif