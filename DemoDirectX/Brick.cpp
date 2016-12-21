#include "Brick.h"


Brick::Brick()
{
    
}

Brick::~Brick()
{

}

bool Brick::init(D3DXVECTOR3 position)
{
    InitWithAnimation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());

    SetPosition(position);

    return true;
}