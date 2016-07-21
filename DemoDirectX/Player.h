#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "Animation.h"
#include "GameGlobal.h"
#include "Camera.h"
#include "PlayerData.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"

const float PLAYER_MAX_JUMP_VELOCITY = 8.0f; //van toc nhay lon nhat
const float PLAYER_MIN_JUMP_VELOCITY = -8.0f; //van toc nhay thap nhat
const float PLAYER_MAX_RUNNING_SPEED = 3.2f; //toc do chay nhanh nhat cua player
const float PLAYER_BOTTOM_RANGE_FALLING = 8.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong

class Player : public Entity
{
public:
    Player();
    ~Player();

    enum PlayerStates
    {
        Standing, 
        Running,
        Falling,
        Jumping,
        Die
    };

    enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
        None //dung im
    };

    void setCamera(Camera *camera);

    void update(float dt);

    void handleKeyboard(std::map<int, bool> keys);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT *sourceRect = NULL, D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXVECTOR2 scalingCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void changeState(PlayerState *newState, Player::PlayerStates stateName);

    void onCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

    void onNoCollisionWithBottom();

    MoveDirection getMoveDirection();

    Player::PlayerStates getState();

    RECT GetBound();     

protected:

    Camera      *mCamera;

    PlayerData *playerData;

    Animation   *currentAnimation,
                *animationStanding,
                *animationRunning,
                *animationJumping;

    void changeAnimation(PlayerStates state);

    PlayerStates currentState;
};

