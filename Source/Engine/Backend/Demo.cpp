#include "Demo.h"

Engine::Demo* Engine::Demo::m_Instance = nullptr;
Engine::Keyboard* Engine::Demo::m_Keyboard = nullptr;

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

    m_Keyboard = new Keyboard();
}

Engine::Demo::~Demo()
{
    UnregisterClass(m_WndClass.c_str(), m_hInst);
    delete(m_Keyboard);
}

void Engine::Demo::OnMouseMoved(int posX, int posY)
{
}

void Engine::Demo::InitWindow()
{
    //HICON icon = static_cast<HICON>(LoadImage(m_hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));

    ZeroMemory(&m_Window, sizeof(m_Window));
    m_Window.cbSize = sizeof(WNDCLASSEX);
    m_Window.style = CS_CLASSDC;
    m_Window.lpfnWndProc = WndProc;
    m_Window.hInstance = m_hInst;
    m_Window.hIcon = static_cast<HICON>(LoadImage(m_hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
    m_Window.hIconSm = static_cast<HICON>(LoadImage(m_hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
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
//
//LRESULT Engine::Demo::WndProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    if (msg == WM_NCCREATE) {
//        //Store a handle to the application using the Create parameter, to access specific methods
//        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
//        Demo* const pInst = static_cast<Demo*>(pCreate->lpCreateParams);
//        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pInst));
//
//        //Set the new Window Procedure 
//        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Demo::WndProcProcess));
//
//        return pInst->WndProc(hWnd, msg, wParam, lParam);
//    }
//
//    return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
//LRESULT Engine::Demo::WndProcProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    Demo* const pInst = reinterpret_cast<Demo*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
//
//    return pInst->WndProc(hWnd, msg, wParam, lParam);
//}

LRESULT __stdcall Engine::Demo::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0xdead);
        return 0;

    //Process any keyboard inputs
    case WM_KEYDOWN:
        m_Keyboard->OnKeyPressed(wParam);
        //OnKeyPressed(wParam);
        break;

    case WM_KEYUP:
        m_Keyboard->OnKeyReleased(wParam);
        //OnKeyReleased(wParam);
        break;

    case WM_MOUSEMOVE:
        //OnMouseMoved(LOWORD(lParam), HIWORD(lParam));
    default:
        break;
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

    m_FramerateLimit = 0;
    m_RNG.Seed(m_Time.BaseTime());

    //m_ObjectPool.Alloc(5000);

    //Fixed Timestep logic
    m_FixedTimestep = 1.0f / 60.0f;
    static float accumulator = 0;
    
    int FPS;
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
            FPS = 1.0f / m_Time.DeltaTime();
            float fixedFrameTime = 1.0f / m_FramerateLimit;

            m_Graphics->Clear(0, 0, 0, 1);
            
            
            if (m_FramerateLimit < FPS && m_FramerateLimit > 0) {
                float sleepTime = 1000 * (fixedFrameTime - m_Time.DeltaTime());

                //Update (Framerate Limited)
                DoFrame(fixedFrameTime);
                Update(fixedFrameTime);

                Sleep(sleepTime);
            }
            else {
                //Update
                DoFrame(m_Time.DeltaTime());
                Update(m_Time.DeltaTime());
            }
            

            while (accumulator >= m_FixedTimestep) {
                //Fixed Update
                FixedUpdate(m_FixedTimestep);
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

void Engine::Demo::FixedUpdate(float dt)
{
}

void Engine::Demo::PreInit()
{
    for (auto& obj : m_Components) {
        if (obj->IsEnabled()) {
            obj->Init();
        }
        
    }
}

void Engine::Demo::DoFrame(float dt)
{
    for (auto& obj : m_Components) {
        if (obj->IsEnabled()) {
            obj->Update(dt);
        }
    }
}

void Engine::Demo::Draw(float dt)
{
    for (auto& obj : m_Components) {
        if (obj->IsEnabled()) {
            obj->Draw(dt);
        }
    }
}

void Engine::Demo::OnKeyPressed(int code)
{
    //m_Keyboard->OnKeyPressed(code);
}

void Engine::Demo::OnKeyReleased(int code)
{
    //m_Keyboard->OnKeyReleased(code);
}
