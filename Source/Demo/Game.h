#pragma once
#include <Backend/Demo.h>

class Game : public Engine::Demo {
public:
    Game(HINSTANCE inst, const std::wstring& wndClass, const std::wstring& wndTitle, int showCommand) 
        : Demo(inst, wndClass, wndTitle, showCommand) 
    {

    }

    //Overrides for invoked methods
    void Update(float dt) override;
    
    void Init() override;
    void Exit() override;

};