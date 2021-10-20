#include <memory>
#include "Demo.h"
#include <Windows.h>
//gameException.h

#if defined(DEBUG) | defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#endif

using namespace Engine; 

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

    std::unique_ptr<Demo> demo(new Demo(inst, L"RenderingDemo",L"Rendering Demo [Default]", showCode));
    //Create Demo instance, throw an error if unsuccessful.
    //try {
    demo->Run();
    //}
    


}