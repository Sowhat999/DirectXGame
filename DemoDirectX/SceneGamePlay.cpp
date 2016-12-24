#include "SceneGamePlay.h"
#include "SceneManager.h"
#include "DemoScene.h"
#include "Transition\TransitionCircleScan.h"
#include "Sound.h"

SceneGamePlay::SceneGamePlay()
{
    LoadContent();
}

SceneGamePlay::~SceneGamePlay()
{
}

void SceneGamePlay::LoadContent()
{
    Scene::LoadContent();
    mMap = new GameMap("marioworld1-1.tmx");
    mMario = new Player();

    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    mCamera->SetPosition(mCamera->GetWidth() / 2, mMap->GetHeight() - mCamera->GetHeight() / 2);

    mMap->SetCamera(mCamera);
    mMario->SetPosition(mCamera->GetPosition());
    mMario->SetCamera(mCamera);

    Sound::getInstance()->loadSound("Resources/man1.wav", "man1");
    Sound::getInstance()->play("man1", false, 1);
    //debug = new GameDebugDraw();
}

void SceneGamePlay::checkCollision()
{
    float widthBottom = 0;
    listCollision.clear();

    mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mMario);
    //mMap->GetQuadTree()->getAllEntities(listCollision);

    for (size_t i = 0; i < listCollision.size(); i++)
    {
        Entity::CollisionReturn r = GameCollision::RecteAndRect(mMario->GetBound(), listCollision.at(i)->GetBound());

        if (r.IsCollided)
        {
            Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mMario, r);
            Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), r);
            
            mMario->OnCollision(listCollision.at(i), r, sidePlayer);
            listCollision.at(i)->OnCollision(mMario, r, sideImpactor);

            if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft || sidePlayer == Entity::BottomRight)
            {
                float bot = r.RegionCollision.right - r.RegionCollision.left;

                if (bot > widthBottom)
                    widthBottom = bot;
            }
        }
    }

    if (widthBottom < mMario->GetWidth() / 4.0f)
    {
        mMario->OnNoCollisionWithBottom();
    }
}
void SceneGamePlay::Update(float dt)
{
    checkCollision();

    mMap->Update(dt);

    mMario->HandleKeyboard(mKeyCodes);
    mMario->Update(dt);

    CheckCameraAndWorldMap();
}

void SceneGamePlay::Draw()
{
    mMap->Draw();

    mMario->Draw();

    //for (auto entity : listCollision)
    //{
    //    debug->DrawRect(entity->GetBound(), mCamera);
    //}

    //drawQuadTree(mMap->GetQuadTree());
}

void SceneGamePlay::OnKeyDown(int keyCode)
{
    mKeyCodes[keyCode] = true;

    mMario->OnKeyPressed(keyCode);
}

void SceneGamePlay::OnKeyUp(int keyCode)
{
    mKeyCodes[keyCode] = false;

    mMario->OnKeyUp(keyCode);
}

void SceneGamePlay::OnMouseDown(float x, float y)
{
    SceneManager::GetInstance()->ReplaceScene(new DemoScene(), new TransitionCircleScan());
}

void SceneGamePlay::CheckCameraAndWorldMap()
{
    mCamera->SetPosition(mMario->GetPosition());

    if (mCamera->GetBound().left < 0)
    {
        //vi position cua camera ma chinh giua camera
        //luc nay o vi tri goc ben trai cua the gioi thuc
        mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
    }

    if (mCamera->GetBound().right > mMap->GetWidth())
    {
        //luc nay cham goc ben phai cua the gioi thuc
        mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2, mCamera->GetPosition().y);
    }

    if (mCamera->GetBound().top < 0)
    {
        //luc nay cham goc tren the gioi thuc
        mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
    }

    if (mCamera->GetBound().bottom > mMap->GetHeight())
    {
        //luc nay cham day cua the gioi thuc
        mCamera->SetPosition(mCamera->GetPosition().x, mMap->GetHeight() - mCamera->GetHeight() / 2);
    }
}

void SceneGamePlay::drawQuadTree(QuadTree * quadtree)
{/*
    if (quadtree->Nodes)
    {
        for (size_t i = 0; i < 4; i++)
        {
            drawQuadTree(quadtree->Nodes[i]);
        }
    }

    debug->DrawRect(quadtree->Bound, mCamera);

    if (quadtree->Nodes)
    {
        for (size_t i = 0; i < 4; i++)
        {
            debug->DrawRect(quadtree->Nodes[i]->Bound, mCamera);
        }
    }*/
}
