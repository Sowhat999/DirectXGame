#pragma once

//xu ly input cua game
//lay tu event cua win32

#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include "GameLog.h"
#include "GameGlobal.h"
#include "IInput.h"

#define KEYBOARD_BUFFERD_SIZE 1024

class GameInput
{
public:
    static GameInput* GetInstance();
    void InitInputDevice();
    void UpdateInput();
    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);
    int IsKeyDown(int keyCode);
    void SetKeyboardUser(IInput *user);
    ~GameInput();

private:
    GameInput();
    static GameInput *mInstance;
    IInput *mInputUser;

    BYTE                    mKeyStates[256];
    DIDEVICEOBJECTDATA      mKeyEvents[1024];
    LPDIRECTINPUTDEVICE8    mKeyboard;
    LPDIRECTINPUT8          mDI;
};
