#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "GameLog.h"
#include "Scene.h"
#include "Transition\SceneTransition.h"
#include "Transition\TransitionEffect.h"

class SceneManager
{
public:
    static SceneManager *GetInstance();
    ~SceneManager();

    Scene* GetCurrentScene();
    void Update(float dt);
    void ReplaceScene(Scene *scene);
    void ReplaceScene(Scene *scenedest, TransitionEffect *effect);
    void OnFinishTransition();

private:
    SceneManager();
    static SceneManager     *mInstace;
    Scene                   *mCurrentScene,
                            *mDestinationScene; // dung cho effect

    static bool             mIsTransitioning;
};

#endif