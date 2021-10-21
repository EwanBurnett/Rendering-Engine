#pragma once

#include <windows.h>
#include <string>
#include "Time.h"
#include "Random.h"
#include "Graphics.h"

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
        virtual void Update();
        virtual void Draw();

    protected:
        virtual void InitWindow();
        virtual void Shutdown();

        static const UINT DefaultScreenWidth;
        static const UINT DefaultScreenHeight;

        HINSTANCE m_hInst;
        std::wstring m_WndClass;
        std::wstring m_WndTitle;
        int m_ShowCmd;

        HWND m_WindowHandle;
        WNDCLASSEX m_Window;

        UINT m_ScreenWidth;
        UINT m_ScreenHeight;

        Time m_Time;

        std::unique_ptr<D3D11_Graphics> m_Graphics;

    private:
        Demo(const Demo& rhs);
        //Demo& operator = (const Demo& rhs);

        POINT CenterWindow(int windowWidth, int windowHeight);
        static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    };

}