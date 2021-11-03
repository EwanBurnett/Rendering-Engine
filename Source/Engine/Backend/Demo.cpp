#include "Demo.h"

Engine::Demo* Engine::Demo::m_Instance = nullptr;

Engine::Demo::Demo(HINSTANCE inst, const std::wstring& wndClass, const std::wstring& wndTitle, int showCommand)
{
    //Set up the singleton for this demo
    assert(m_Instance == nullptr);
    m_Instance = this;

    
    

    m_hInst = inst;
    m_WndClass = wndClass;
    m_WndTitle = wndTitle;
    m_ShowCmd = showCommand;
    
    m_ScreenWidth = 1600;
    m_ScreenHeight = 900;
}

Engine::Demo::~Demo()
{
    UnregisterClass(m_WndClass.c_str(), m_hInst);
}

void Engine::Demo::InitWindow()
{
    ZeroMemory(&m_Window, sizeof(m_Window));
    m_Window.cbSize = sizeof(WNDCLASSEX);
    m_Window.style = CS_CLASSDC;
    m_Window.lpfnWndProc = WndProc;
    m_Window.hInstance = m_hInst;
    m_Window.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    m_Window.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    m_Window.hCursor = LoadCursor(nullptr, IDC_ARROW);
    m_Window.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    m_Window.lpszClassName = m_WndClass.c_str();

    RECT windowRect = { 0, 0, (LONG)m_ScreenWidth, (LONG)m_ScreenHeight };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);  //Calculate client region size

    RegisterClassEx(&m_Window);

    POINT center = CenterWindow(m_ScreenWidth, m_ScreenHeight);
    m_WindowHandle = CreateWindow(m_WndClass.c_str(), m_WndTitle.c_str(), WS_OVERLAPPEDWINDOW, center.x, center.y, windowRect.right, windowRect.bottom, nullptr, nullptr, m_hInst, nullptr);

    ShowWindow(m_WindowHandle, m_ShowCmd);
    UpdateWindow(m_WindowHandle);
    
    m_Graphics = std::make_unique<D3D11_Graphics>(m_WindowHandle, m_ScreenWidth, m_ScreenHeight);
    
}

void Engine::Demo::Shutdown()
{
    Exit();
}

//Demo& Engine::Demo::operator=(const Demo& rhs)
//{
//    // TODO: insert return statement here
//}

POINT Engine::Demo::CenterWindow(int windowWidth, int windowHeight)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    POINT center;
    center.x = (screenWidth - windowWidth) / 2;
    center.y = (screenHeight - windowHeight) / 2;
    return center;
}

LRESULT __stdcall Engine::Demo::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0xdead);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Engine::Demo::Run()
{
    InitWindow();

    MSG message;
    ZeroMemory(&message, sizeof(message));

    m_Time.Reset();
    m_Time.SetTimeScale(1.0f);

    m_RNG.Seed(m_Time.BaseTime());

    //m_ObjectPool.Alloc(5000);

    //Fixed Timestep logic
    m_FixedTimestep = 1.0f / 60.0f;
    static float accumulator = 0;

    //Initialize the Demo
    Init();
    PreInit();

    while (message.message != WM_QUIT) {
        if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else {
            //Pre-Update
            m_Time.Tick();
            accumulator += m_Time.DeltaTime();

            m_Graphics->Clear(0, 0, 0, 1);
            
            //Update
            DoFrame(m_Time.DeltaTime());
            Update(m_Time.DeltaTime());

            while (accumulator >= m_FixedTimestep) {
                //Fixed Update
                accumulator -= m_FixedTimestep;
            }

            Draw(m_Time.DeltaTime());

            m_Graphics->Swapchain()->Present(0, 0);
            //Post-Update
        }
    }

    Shutdown();
}

void Engine::Demo::Exit()
{
}

void Engine::Demo::Init()
{
}

void Engine::Demo::Update(float dt)
{
    
}

void Engine::Demo::PreInit()
{
    for (auto& obj : m_Components) {
        obj->Init();
    }
}

void Engine::Demo::DoFrame(float dt)
{
    for (auto& obj : m_Components) {
        obj->Update(dt);
    }
}

void Engine::Demo::Draw(float dt)
{
    for (auto& obj : m_Components) {
        obj->Draw(dt);
    }
}
