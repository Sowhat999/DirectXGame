#include "Scene.h"


Scene::Scene()
{
    mSpriteHandler = GameGlobal::GetCurrentSpriteHandler();
    mBackColor = 0x4866ff;
    LoadContent();
}


Scene::~Scene()
{

}

void Scene::Update(float dt)
{

}

void Scene::LoadContent()
{
    if (!mSpriteHandler)
        mSpriteHandler = GameGlobal::GetCurrentSpriteHandler();
}

void Scene::Draw()
{

}

void Scene::Render()
{
    auto device = GameGlobal::GetCurrentDevice();

    //begin render
    device->Clear(0, NULL, D3DCLEAR_TARGET, this->mBackColor, 0.0f, 0);
    device->BeginScene();

    //draw
    GameGlobal::GetCurrentSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
    Draw();
    GameGlobal::GetCurrentSpriteHandler()->End();

    //end render
    device->EndScene();
    device->Present(NULL, NULL, NULL, NULL);        
}

void Scene::OnKeyDown(int keyCode)
{

}

void Scene::OnKeyUp(int keyCode)
{
    
}

void Scene::OnMouseDown(float x, float y)
{

}

bool Scene::IsKeyPress(int keyCode)
{
    return GameInput::GetInstance()->IsKeyDown(keyCode);
}

D3DCOLOR Scene::GetBackcolor()
{
    return mBackColor;
}

void Scene::DoEndScene()
{

}