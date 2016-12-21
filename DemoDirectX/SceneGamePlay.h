#ifndef __SCENE_GAMEPLAY__
#define __SCENE_GAMEPLAY__

#include "Scene.h"
#include "GameLog.h"
#include "GameMap.h"
#include "Player.h"

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

    void checkCollision();

private:
    void CheckCameraAndWorldMap();

    float angle;
    GameMap *mMap;
    Camera *mCamera;
    Player *mMario;

    std::map<int, bool>     mKeyCodes;
};

#endif