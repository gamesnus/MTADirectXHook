#pragma once

#include <d3d9.h>

class Menu
{
    bool state = true;
    bool initialized = false;

public:
    bool getState() { return state; }
    bool toggleState()
    {
        state = !state;
        return state;
    }

    void Init(IDirect3DDevice9* device);
    void Draw();
    void Reset(bool before);
};

extern Menu* menu;