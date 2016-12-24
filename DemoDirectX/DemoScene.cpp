#include "DemoScene.h"

DemoScene::DemoScene()
{
    mBackColor = 0x54acd2;

    LoadContent();
}

void DemoScene::LoadContent()
{
    mMap = new GameMap("mapdemo.tmx");
    auto mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    mCamera->SetPosition(mCamera->GetWidth() / 2, mMap->GetHeight() - mCamera->GetHeight() / 2);
    mMap->SetCamera(mCamera);
}

void DemoScene::Update(float dt)
{
    
}

void DemoScene::Draw()
{
    mMap->Draw();
}

void DemoScene::DoEndScene()
{
    
}