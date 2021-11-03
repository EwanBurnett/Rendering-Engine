#include <memory>
#include <Windows.h>
#include "Game.h"

#if defined(DEBUG) | defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif


int WINAPI WinMain(
    HINSTANCE inst,
    HINSTANCE prevInst,     //Unused 
    LPSTR cmd,
    int showCode
)
{
#if defined(DEBUG) | defined(_DEBUG)
    //Set Memory leak and allocation flags in debug configuration
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    Game* game = new Game(inst, L"RenderingDemo",L"Rendering Demo [Default]", showCode);
    game->Run();
    
}