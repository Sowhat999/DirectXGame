#include "QuadTree.h"

int QuadTree::TotalCallBackCall = 0;

QuadTree::QuadTree()
{
}

QuadTree::~QuadTree()
{
}

QuadTree::QuadTree(int level, RECT bound)
{
    //chia lam 4

    this->Bound = bound;
    this->mLevel = level;
    this->Nodes = nullptr;
}

void QuadTree::Clear()
{
    if (Nodes)
    {
        for (size_t i = 0; i < 4; i++)
        {
            if (Nodes[i])
            {
                Nodes[i]->Clear();
                delete Nodes[i];
                Nodes[i] = nullptr;
            }
        }

        delete[] Nodes;
    }
}

void QuadTree::insertEntity(Entity *entity)
{
    int index = getIndex(entity->GetBound());

    if (index == -1)
    {       
        ListEntity.push_back(entity);
    }
    else
    {
        if (Nodes == nullptr)
        {
            split();
        }

        Nodes[index]->insertEntity(entity);
    }
}

bool QuadTree::isContain(Entity *entity)
{
    RECT r = entity->GetBound();

    if (r.left >= Bound.left && r.right <= Bound.right && r.top >= Bound.top && r.bottom <= Bound.bottom)
    {
        return true;
    }

    return false;
}

void QuadTree::split()
{
    //cat phan region (ranh gioi) ra thanh 4 phan bang nhau
    Nodes = new QuadTree * [4];

    RECT bound;

    int width = (Bound.right - Bound.left) / 2;
    int height = (Bound.bottom - Bound.top) / 2;

    //phan goc trai tren
    bound.left = Bound.left;
    bound.right = bound.left + width;
    bound.top = Bound.top;
    bound.bottom = bound.top + height;
    Nodes[0] = new QuadTree(mLevel + 1, bound);

    //phan goc phai tren
    bound.left = Bound.left + width;
    bound.right = bound.left + width;
    bound.top = Bound.top;
    bound.bottom = bound.top + height;
    Nodes[1] = new QuadTree(mLevel + 1, bound);

    //phan goc trai duoi
    bound.left = Bound.left;
    bound.right = bound.left + width;
    bound.top = Bound.top + height;
    bound.bottom = bound.top + height;
    Nodes[2] = new QuadTree(mLevel + 1, bound);

    //phan goc phai duoi
    bound.left = Bound.left + width;
    bound.right = bound.left + width;
    bound.top = Bound.top + height;
    bound.bottom = bound.top + height;
    Nodes[3] = new QuadTree(mLevel + 1, bound);
}

int QuadTree::getTotalEntities()
{
    int total = ListEntity.size();

    if (Nodes)
    {
        for (size_t i = 0; i < 4; i++)
        {
            total += Nodes[i]->getTotalEntities();
        }
    }

    return total;
}

int QuadTree::getIndex(RECT body)
{
    /*lay vi tri cua Entity
    0: nam trong Node con goc trai tren
    1: nam trong Node con goc phai tren
    2: nam trong Node con goc trai duoi
    3: nam trong Node con goc phai duoi
    -1: bi dinh > 2 node con*/

    float middleVerticle = Bound.left + (Bound.right - Bound.left) / 2.0f;
    float middleHorizontal = Bound.top + (Bound.bottom - Bound.top) / 2.0f;

    if (body.top >= Bound.top && body.bottom <= middleHorizontal)
    {
        //nam phia ben tren
        if (body.left >= Bound.left && body.right <= middleVerticle)
        {
            //nam phia ben trai
            return 0;
        }
        else if (body.left >= middleVerticle && body.right <= Bound.right)
        {
            //nam phia ben phai
            return 1;
        }
    }
    else
    {
        //nam phia ben duoi
        if (body.left >= Bound.left && body.right <= middleVerticle)
        {
            //nam phia ben trai
            return 2;
        }
        else if (body.left >= middleVerticle && body.right <= Bound.right)
        {
            //nam phia ben phai
            return 3;
        }
    }

    return -1;
}

void QuadTree::getAllEntities(std::vector<Entity*> &entitiesOut)
{
    if (Nodes)
    {
        for (size_t i = 0; i < 4; i++)
        {
            Nodes[i]->getAllEntities(entitiesOut);
        }
    }

    for (std::vector<Entity*>::iterator i = this->ListEntity.begin(); i != this->ListEntity.end(); i++)
    {
        entitiesOut.push_back(*i);
    }
}

void QuadTree::getEntitiesCollideAble(std::vector<Entity*> &entitiesOut, Entity *entity)
{
    int index = this->getIndex(entity->GetBound());

    if (index == -1)
    {
        //nam trong >= 2 node con
        //this->getAllEntities(entitiesOut);
    }
    else
    {
        if (Nodes)
        {            
            for (size_t i = 0; i < 4; i++)
            {
                //lay index cua entity
                Nodes[i]->getEntitiesCollideAble(entitiesOut, entity);
            }
        }
    }

    //nam trong 1 node con nao do
    for (size_t i = 0; i < ListEntity.size(); i++)
    {
        entitiesOut.push_back(ListEntity.at(i));
    }
}