#ifndef __QUAD_TREE__
#define __QUAD_TREE__
#include "GameLog.h"
#include <d3dx9.h>
#include <d3d9.h>
#include "GameCollision.h"
#include <vector>
#include "Camera.h"
#include "GameGlobal.h"
#include "Entity.h"

//#define QUADTREE_MAX_LEVEL 6 //so node con toi da

class QuadTree
{
public:

    QuadTree(int level, RECT bound);
    ~QuadTree();
    void Clear();
    void insertEntity(Entity *entity);
    QuadTree **Nodes;
    std::vector<Entity*> mListEntity; //danh sach cac phan tu co trong vung va cham (Bound)
    
    //lay danh sach nhung Entity co kha nang xay ra va cham
    void getEntitiesCollideAble(std::vector<Entity*> &entitiesOut,Entity *entity); // tra ve danh sach cac phan tu nam trong vung va cham
    void getAllEntities(std::vector<Entity*> &entitiesOut);
    int getTotalEntities();
    static int TotalCallBackCall;
    static void debugConsole(QuadTree *tree);

    RECT Bound;

protected:
    /*lay vi tri cua Entity 
    0: nam trong Node con goc trai tren
    1: nam trong Node con goc phai tren
    2: nam trong Node con goc trai duoi
    3: nam trong Node con goc phai duoi
    -1: bi dinh > 2 node con*/
    int getIndex(RECT body);

    void split(); //thuc hien chia ra cac node
    bool isContain(Entity *entity);
    int mLevel; //tuong ung voi so node
};

#endif