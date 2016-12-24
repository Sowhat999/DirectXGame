#ifndef __SCENE_GAMEPLAY__
#define __SCENE_GAMEPLAY__

#include "Scene.h"
#include "GameLog.h"
#include "GameMap.h"
#include "Player.h"
#include "GameDebugDraw.h"

class SceneGamePlay : public Scene
{
public:

    /*
    TypeBrick: xac dinh va cham la vien gach
    TypeEnemy: xac dinh va cham la ke thu
    TypeMario: xac dinh va cham la mario
    TypeStatic: xac dinh va cham la dia hinh tinh (lay tu object trong map)
    */

    SceneGamePlay();
    ~SceneGamePlay();

    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);

    void checkCollision();

private:
    void CheckCameraAndWorldMap();
    void drawQuadTree(QuadTree *quadtree);

    float angle;
    GameMap *mMap;
    Camera *mCamera;
    Player *mMario;
    //GameDebugDraw *debug;
    std::vector<Entity*> listCollision;

    std::map<int, bool>     mKeyCodes;
};

#endif