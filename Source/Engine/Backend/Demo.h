#pragma once

#include <windows.h>
#include <string>
#include "..\Utils\Time.h"
#include "..\Utils\Random.h"
#include "..\Backend\Graphics.h"
#include "..\Backend\ObjectPool.h"
#include "..\Utils\Input.h"
#include "..\Components\Camera.h"
#include "..\resource.h"

namespace Engine
{
    class Demo {
    public:
        Demo(HINSTANCE inst, const std::wstring& wndClass, const std::wstring& wndTitle, int showCommand);
        virtual ~Demo();

        HINSTANCE Instance() const;
        HWND WindowHandle() const;
        const WNDCLASSEX& Window() const;
        const std::wstring& WindowClass() const;
        const std::wstring& WindowTitle() const;

        int ScreenWidth() const;
        int ScreenHeight() const;

        virtual void Run();
        virtual void Exit();
        virtual void Init();
        virtual void Update(float dt);
        virtual void FixedUpdate(float dt);

        void PreInit();
        void DoFrame(float dt);
        void DoFixedFrame(float dt);
        void Draw(float dt);

    protected:
        void OnKeyPressed(int code);
        void OnKeyReleased(int code);

        void OnMouseButtonPressed(int code);
        void OnMouseButtonReleased(int code);
        void OnMouseMoved(int posX, int posY);

        virtual void InitWindow();
        virtual void Shutdown();

        static const UINT DefaultScreenWidth;
        static const UINT DefaultScreenHeight;


        void SetFrameRate(int fps);

        HINSTANCE m_hInst;
        std::wstring m_WndClass;
        std::wstring m_WndTitle;
        int m_ShowCmd;

        HWND m_WindowHandle;
        WNDCLASSEX m_Window;

        UINT m_ScreenWidth;
        UINT m_ScreenHeight;

        Time m_Time;
        float m_FixedTimestep;
        int m_FramerateLimit;
        RNG m_RNG;
        Camera* m_Camera;

        static Keyboard* m_Keyboard;
        
        //Engine::ObjectPool m_ObjectPool;
        std::vector<Engine::GameComponent*> m_Components;  //TODO: Replace with Object Pooling
        std::unique_ptr<D3D11_Graphics> m_Graphics;

    private:
        Demo(const Demo& rhs);
        //Demo& operator = (const Demo& rhs);

        //Singleton for the Demo 
        static Demo* m_Instance;

        POINT CenterWindow(int windowWidth, int windowHeight);
      /*  static LRESULT CALLBACK WndProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK WndProcProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);*/
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



    };

}