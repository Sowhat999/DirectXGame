#pragma once
#include "TransitionEffect.h"
#include "../Scene.h"

class SceneTransition
{
public:
    static SceneTransition* GetInstance();

    void Update(float dt);
    void SetTransition(Scene* source, Scene* dest, TransitionEffect* transition);    
    bool IsFinishTransition();
    Scene* sourceScene;

private:
    SceneTransition();
    ~SceneTransition();

    static SceneTransition* instance;

    TransitionEffect* transition;
};

