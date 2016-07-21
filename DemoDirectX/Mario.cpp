#include "Mario.h"

Mario::Mario(GameMap *gameMap)
{
    mCurrentAnimation = nullptr; //  new Animation();
    //mCurrentAnimation->SetFlipVertical(true);
    mIsFlipHorizontal = mIsFlipVertical = false;
    posX = posY = 0;


    //khoi tao dung ham initwithanimation
    this->mMap = gameMap;

    mGravity = D3DXVECTOR3(0, 5, 0);
    mSpeedX = RUN_VELOCITY_KEY_PRESS; //RUN_VELOCITY_KEY_HOLDING;
    mCurrentJumpVelocity = JUMP_VELOCITY;
    mJumpHigh = 350; //cho phep nhay cao them 80 pixel
    mJumpVelocity = 8;
    mState = Mario::MarioStates::Standing;
    mSide = Mario::MarioSides::Right;

    LoadAnimations();

    this->width = mCurrentAnimation->getWidth();
    this->height = mCurrentAnimation->getHeight();

    IsCollideTop = IsCollideBottom = IsCollideLeft = IsCollideRight = false;
}

Mario::~Mario()
{
    
}

void Mario::SetGravity(D3DXVECTOR3 gravity)
{
    this->mGravity = gravity;
}

D3DXVECTOR3 Mario::GetGravity()
{
    return mGravity;
}

void Mario::SetPosition(D3DXVECTOR3 pos)
{
    this->posX = pos.x;
    this->posY = pos.y;

    mCurrentAnimation->SetPosition(pos);
}

void Mario::SetPosition(float x, float y)
{
    this->posX = x;
    this->posY = y;

    mCurrentAnimation->SetPosition(D3DXVECTOR3(x, y, 0));
}

void Mario::SetFlipVertical(bool flag)
{
    mIsFlipVertical = flag;
}

void Mario::SetAllowMove(bool flag)
{
    mIsAllowMove = flag;
}

void Mario::SetFlipHorizontal(bool flag)
{
    mIsFlipHorizontal = flag;
}

int Mario::GetWidth()
{
    return (mCurrentAnimation)->getWidth();
}

int Mario::GetHeight()
{
    return (mCurrentAnimation)->getHeight();
}

void Mario::SetCurrentVelocity(D3DXVECTOR3 velocity)
{
    vx = velocity.x;
    vy = velocity.y;
}

void Mario::SetCurrentJumpVelocity(float velocity)
{
    mCurrentJumpVelocity = velocity;
}

float Mario::GetCurrentJumpVelocity()
{
    return mCurrentJumpVelocity;
}

float Mario::GetSpeedX()
{
    return mSpeedX;
}

void Mario::SetSpeedX(float x)
{
    mSpeedX = x;
}

void Mario::ActiveSpeedKeyPress()
{
    this->SetSpeedX(RUN_VELOCITY_KEY_PRESS);
}

void Mario::SetGameMap(GameMap *map)
{
    mMap = map;
}

GameMap* Mario::GetGameMap()
{
    return mMap;
}

float Mario::GetSpeedYDefault()
{
    return mSpeedYDefault;
}

void Mario::SetState(MarioStates state)
{
    mState = state;

    switch (state)
    {
    case MarioStates::Running:
        //this->SetSpeedX(RUN_VELOCITY_KEY_HOLDING);
        if (this->GetSpeedX() > 0)
            mCurrentAnimation = mAnimationRunning;
        break;

    case MarioStates::Jumping:case MarioStates::JumpingAndMoving:
        mCurrentJumpVelocity = JUMP_VELOCITY;
        mCurrentAnimation = mAnimationJumping;
        break;

    case MarioStates::Standing: 
        mCurrentAnimation = mAnimationStanding;
        mCurrentJumpVelocity = 0;
        break;

    case MarioStates::FallingDown:
        mCurrentAnimation = mAnimationJumping;
        //mSpeedX = 0;
        break;

    case MarioStates::FallingDownAndMoving:
        mSpeedX = RUN_VELOCITY_KEY_HOLDING;
        mCurrentAnimation = mAnimationJumping;
        break;

    case MarioStates::DroppingDown: case MarioStates::DroppingDownAndMoving:
        mCurrentAnimation = mAnimationJumping;
        break;

    case MarioStates::TurningBack:
        this->SetSpeedX(TURNING_BACK_VELOCITY);
        mCurrentAnimation = mAnimmationTurningBack;
        break;
    }
}

Mario::MarioStates Mario::GetState()
{
    return mState;
}

void Mario::SetSide(MarioSides side)
{
    mSide = side;
}

Mario::MarioSides Mario::GetSide()
{
    return mSide;
}

void Mario::SetJumpHigh(float high)
{
    mJumpHigh = high;
}

float Mario::GetJumpHigh()
{
    return mJumpHigh;
}

RECT Mario::GetBoundInWorld()
{
    RECT bound;
    bound.left = posX - (mCurrentAnimation)->getWidth() / 2;
    bound.right = bound.left + (mCurrentAnimation)->getWidth();
    bound.top = posY - (mCurrentAnimation)->getHeight() / 2;
    bound.bottom = bound.top + (mCurrentAnimation)->getHeight();

    return bound;
}

void Mario::SetCamera(Camera *camera)
{
    mCamera = camera;
}

Camera* Mario::GetCamera()
{
    return mCamera;
}

void Mario::Draw()
{
    mCurrentAnimation->SetFlipHorizontal(mIsFlipHorizontal);
    mCurrentAnimation->SetFlipVertical(mIsFlipVertical);
    mCurrentAnimation->SetPosition(D3DXVECTOR3(posX, posY,0));

    if (mCamera)
    {
        //doi hinh mario tu vi tri trong real world sang man hinh
        D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - this->mCamera->GetPosition().x,
            GameGlobal::GetHeight() / 2 - this->mCamera->GetPosition().y);

        (mCurrentAnimation)->Draw(D3DXVECTOR3(posX, posY, 0), NULL, D3DXVECTOR2(), trans);
    }
    else
        (mCurrentAnimation)->Draw(D3DXVECTOR3(posX, posY, 0));
}

void Mario::update(float dt)
{    
    Entity::update(dt);

    mCurrentAnimation->Update(dt);
}

void Mario::LoadAnimations()
{
    mAnimationStanding = new Animation("mario/standingright.png", 1, 1, 1, 0);
    mAnimationJumping = new Animation("mario/jumpingright.png", 1, 1, 1, 0);
    mAnimationRunning = new Animation("mario/runningright.png", 2, 1, 2, 0.15f);
    mAnimmationTurningBack = new Animation("mario/turnback.png", 1, 1, 1, 0);

    mCurrentAnimation = mAnimationStanding;
}

void Mario::handleKeyboard(std::map<int, bool> keys)
{

}