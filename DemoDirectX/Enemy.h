#ifndef __EMEMY__
#define __EMEMY__

#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "Animation.h"
#include "GameGlobal.h"
#include "Camera.h"
#include "QuadTree.h"
#include "EnemyData.h"
#include "EnemyState.h"

class Enemy : public Animation
{
public:    
    enum EnemyStates
    {
        Alive, Die
    };

    enum EnemyName
    {
        MushRoom
    };

    ~Enemy();

    void SetGravity(D3DXVECTOR3 gravity);

    virtual void setCamera(Camera *camera);

    virtual void Update(float dt);

    virtual void handleKeyboard(std::map<int, bool> keys);

    virtual void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    virtual void changeState(EnemyState *newState);

protected:
    Enemy();

    D3DXVECTOR3 mGravity;
    EnemyName   mName;
    Camera      *mCamera;

    EnemyData *enemyData;
};

#endif