//#include "GameScene.h"
//#include "PlayerFallingState.h"
//#include "GameCollision.h"
//
//GameScene::GameScene(char *mapfilePath)
//{
//    mMapPath = mapfilePath;
//
//}
//
//GameScene::~GameScene()
//{
//
//}
//
//void GameScene::LoadContent()
//{
//    mTimeArrowLeftHolding = mTimeArrowRightHolding = mTimeSpaceHolding = 0;
//
//    mGravity = D3DXVECTOR3(0, 3, 0);
//    //load map
//
//    mGameMap = new GameMap(mMapPath);
//    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
//    mCamera->SetPosition(mCamera->GetWidth() / 2, mGameMap->GetHeight() - mCamera->GetHeight() / 2);
//
//    //chỉnh tọa độ camera cho vị trí góc dưới map
//    //vị trí của camera tương ứng với vị trí trong thế giới thực, tuy hiên position là vị trí tâm của camera
//    mGameMap->SetCamera(mCamera);
//
//    //quadtree cho map
//    RECT quadBound;
//    quadBound.left = quadBound.top = 0;
//    quadBound.right = mGameMap->GetWidth();
//    quadBound.bottom = mGameMap->GetHeight();
//    mQuadTree = new QuadTree(1, quadBound);
//
//
//
//    RECT sourceRECT; //vien gach
//    sourceRECT.left = 32; //toa do x trong tileset
//    sourceRECT.top = 0; //toa do y trong tileset
//    sourceRECT.right = sourceRECT.left + 32;
//    sourceRECT.bottom = sourceRECT.top + 32;
//
//    mSpriteBricks = new Sprite("mariotileset.png", &sourceRECT);
//
//    //brick gold
//    sourceRECT.left = 32 * 24; //toa do x trong tileset
//    sourceRECT.top = 0; //toa do y trong tileset
//    sourceRECT.right = sourceRECT.left + 32;
//    sourceRECT.bottom = sourceRECT.top + 32;
//    mSpriteBrickGold = new Sprite("mariotileset.png", &sourceRECT);
//
//    mGameDebugDraw = new GameDebugDraw(GameGlobal::GetCurrentSpriteHandler());
//
//    //mListEnemies.push_back(new EnemyMushRoom(758, mGameMap->GetHeight() - 80, mCamera));
//    mListEnemies.push_back(new EnemyMushRoom(1312, mGameMap->GetHeight() - 80, mCamera));
//
//    player = new Player();
//    player->SetPosition(60, mGameMap->GetHeight() - 190);
//    mCamera->SetPosition(player->GetPosition());
//    player->setCamera(this->mCamera);
//    
//    LoadMapData();
//}
//
//void GameScene::Update(float dt)
//{
//    HandleInput(dt);
//
//    mGameMap->Update(dt);
//    player->update(dt);
//
//    for (size_t i = 0; i < mListEnemies.size(); i++)
//    {
//        mListEnemies.at(i)->Update(dt);
//    }
//
//    mCamera->SetPosition(player->GetPosition());
//
//    CheckCameraAndWorldMap();
//
//    checkCollision();
//}
//
//void GameScene::checkCollision()
//{
//    bool playerBottomCollision = false;
//
//    std::vector<Entity*> list;
//
//    //mQuadTree->getEntitiesCollideAble(list, player);
//    mQuadTree->getAllEntities(list);
//
//    //GAMELOG("size collision: %d", list.size());
//
//    for (size_t i = 0; i < list.size(); i++)
//    {
//        Entity::CollisionReturn r = GameCollision::RectangleAndRectangle(player->GetBound(), list.at(i)->GetBound());
//
//        if (r.IsCollided)
//        {
//            Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(player, r);
//            Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(list.at(i), r);
//
//            player->onCollision(list.at(i), r, sidePlayer);
//            list.at(i)->OnCollision(player, r, sideImpactor);
//
//            if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft || sidePlayer == Entity::BottomRight)
//            {
//                playerBottomCollision = true;
//            }
//        }
//    }
//
//
//    if (!playerBottomCollision)
//    {
//        player->onNoCollisionWithBottom();
//    }
//}
//
//void GameScene::LoadMapData()
//{
//    //khoi tao cac khoi Brick (vien gach)
//#pragma region -BRICK AND COIN LAYER-
//    for (size_t i = 0; i < mGameMap->GetMap()->GetNumTileLayers(); i++)
//    {
//        const Tmx::TileLayer *layer = mGameMap->GetMap()->GetTileLayer(i);
//
//        if (layer->IsVisible())
//            continue;
//
//        //xac dinh layer Brick bi an di de tu do tao ra cac vien gach trong game, nhung vien gach khong phai la 1 physic static nos co the bi pha huy duoc
//
//        if (layer->GetName() == "brick" || layer->GetName() == "coin")
//        {
//            for (size_t j = 0; j < mGameMap->GetMap()->GetNumTilesets(); j++)
//            {
//                const Tmx::Tileset *tileSet = mGameMap->GetMap()->GetTileset(j);
//
//                int tileWidth = mGameMap->GetMap()->GetTileWidth();
//                int tileHeight = mGameMap->GetMap()->GetTileHeight();
//
//                int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
//                int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;
//
//                for (size_t m = 0; m < layer->GetHeight(); m++)
//                {
//                    for (size_t n = 0; n < layer->GetWidth(); n++)
//                    {
//                        if (layer->GetTileTilesetIndex(n, m) != -1)
//                        {
//                            int tileID = layer->GetTileId(n, m);
//
//                            int y = tileID / tileSetWidth;
//                            int x = tileID - y * tileSetWidth;
//
//                            RECT sourceRECT;
//                            sourceRECT.top = y * tileHeight;
//                            sourceRECT.bottom = sourceRECT.top + tileHeight;
//                            sourceRECT.left = x * tileWidth;
//                            sourceRECT.right = sourceRECT.left + tileWidth;
//
//                            RECT bound;
//                            bound.left = n * tileWidth;
//                            bound.top = m * tileHeight;
//                            bound.right = bound.left + tileWidth;
//                            bound.bottom = bound.top + tileHeight;
//
//                            D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);
//
//                            Brick *brick = new Brick(bound, &sourceRECT, position);
//
//                            if (layer->GetName() == "coin")
//                            {
//                                brick->Tag = Entity::EntityTypes::BrickGoldNormal;
//                                mListBrickGold.push_back(brick);
//                            }
//                            else
//                            {
//                                brick->Tag = Entity::EntityTypes::Brick;
//                                mListBrick.push_back(brick);
//                            }
//
//                            brick->name = "Brick";
//
//                            mQuadTree->insertEntity(brick);
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//#pragma endregion
//
//#pragma region -OBJECTGROUP, STATIC OBJECT-
//
//    for (size_t i = 0; i < mGameMap->GetMap()->GetNumObjectGroups(); i++)
//    {
//        const Tmx::ObjectGroup *objectGroup = mGameMap->GetMap()->GetObjectGroup(i);
//
//        for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
//        {
//            Tmx::Object *object = objectGroup->GetObjects().at(j);
//
//            Entity *entity = new Entity();
//            
//            entity->posX = object->GetX() + object->GetWidth() / 2;
//            entity->posY = object->GetY() + object->GetHeight() / 2;
//            entity->width = object->GetWidth();
//            entity->height = object->GetHeight();
//
//            entity->Tag = Entity::EntityTypes::Static;
//            entity->name = "static object";
//            mQuadTree->insertEntity(entity);
//
//        }
//    }
//#pragma endregion
//}
//
//std::vector<Enemy*> GameScene::GetListEnemies()
//{
//    return mListEnemies;
//}
//
//std::vector<Brick*> GameScene::GetListBrick()
//{
//    return mListBrick;
//}
//
//std::vector<Brick*> GameScene::GetListBrickGold()
//{
//    return mListBrickGold; 
//}
//
//GameMap* GameScene::GetMap()
//{
//    return mGameMap;
//}
//
//void GameScene::SetCamera(Camera *camera)
//{
//    mCamera = camera;
//}
//
//Camera* GameScene::GetCamera()
//{
//    return mCamera;
//}
//
//void GameScene::HandleInput(float dt)
//{
//    player->handleKeyboard(mKeyCodes);
//}
//
//bool GameScene::IsKeyPress(int keyCode)
//{
//    return (GameInput::GetInstance()->IsKeyDown(keyCode));
//}
//
//void GameScene::OnKeyDown(int keyCode)
//{
//    mKeyCodes[keyCode] = true;
//}
//
//void GameScene::OnKeyUp(int keyCode)
//{
//    mKeyCodes[keyCode] = false;
//}
//
//void GameScene::CheckCameraAndWorldMap()
//{
//    if (mCamera->GetBound().left < 0)
//    {
//        //vi position cua camera ma chinh giua camera
//        //luc nay o vi tri goc ben trai cua the gioi thuc
//        mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
//    }
//
//    if (mCamera->GetBound().right > mGameMap->GetWidth())
//    {
//        //luc nay cham goc ben phai cua the gioi thuc
//        mCamera->SetPosition(mGameMap->GetWidth() - mCamera->GetWidth() / 2, mCamera->GetPosition().y);
//    }
//
//    if (mCamera->GetBound().top < 0)
//    {
//        //luc nay cham goc tren the gioi thuc
//        mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
//    }
//
//    if (mCamera->GetBound().bottom > mGameMap->GetHeight())
//    {
//        //luc nay cham day cua the gioi thuc
//        mCamera->SetPosition(mCamera->GetPosition().x, mGameMap->GetHeight() - mCamera->GetHeight() / 2);
//    }
//}
//
//void GameScene::Draw()
//{   
//    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
//        GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
//
//    for (size_t i = 0; i < mListBrick.size(); i++)
//    {
//
//
//        mSpriteBricks->Draw(mListBrick.at(i)->GetPosition(), NULL, D3DXVECTOR2(), trans);
//
//        //mGameDebugDraw->DrawRect(mListBrick.at(i)->GetBoundOnScreen(mCamera));
//    }
//
//    for (size_t i = 0; i < mListBrickGold.size(); i++)
//    {
//        mSpriteBrickGold->Draw(mListBrickGold.at(i)->GetPosition(), NULL, D3DXVECTOR2(), trans);
//    }
//
//    mGameMap->Draw();
//    player->Draw();
//
//    for (size_t i = 0; i < mListEnemies.size(); i++)
//    {
//        mListEnemies.at(i)->Draw();
//    }
//
//    drawQuadTree(mQuadTree);
//}
//
//void GameScene::drawQuadTree(QuadTree *quadtree)
//{
//    if (quadtree->Nodes)
//    {
//        for (size_t i = 0; i < 4; i++)
//        {
//            drawQuadTree(quadtree->Nodes[i]);  
//        }
//    }
//
//    mGameDebugDraw->DrawRect(quadtree->Bound, mCamera);
//
//    for (size_t i = 0; i < quadtree->ListEntity.size(); i++)
//    {
//        mGameDebugDraw->DrawRect(quadtree->ListEntity.at(i)->GetBound(), mCamera);
//    }
//}