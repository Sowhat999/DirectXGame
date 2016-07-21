#pragma once
//pre declare
class EnemyState;
class Enemy;

class EnemyData
{
public:
    EnemyData();
    ~EnemyData();

    Enemy *enemy;
    EnemyState *state;
};

