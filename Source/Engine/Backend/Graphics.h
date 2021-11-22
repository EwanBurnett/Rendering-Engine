//DirectX 11 Graphics Backend
//Ewan Burnett 2021
//A Singleton class, which contains Initialization methods for DX11, 
//as well as accessor methods for the D3D11 Device and Context interfaces.
#pragma once

#include <windows.h>
#include <exception>
#include <cassert>
#include <string>
#include <memory>

#include <map>
#include <vector>

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <wrl/client.h>

#include <d3dx11effect.h>

using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;

namespace Engine {
    typedef unsigned char byte;
}

class D3D11_Graphics {
public:
    D3D11_Graphics(HWND &hWnd, UINT width, UINT height);
    ~D3D11_Graphics();

    bool Init();
    void Clear(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

    void SetFramerate(int fps);

    //Returns the ID3D11 Device Context
    ComPtr<ID3D11DeviceContext> Context();
    //Returns the ID3D11 Device
    ComPtr<ID3D11Device> Device();
    //Returns the IDXGI SwapChain
    ComPtr<IDXGISwapChain> Swapchain();

private:
    HRESULT CreateSwapChain();

    //D3D11 Pointers
    ComPtr<ID3D11Device> m_pDevice;
    ComPtr<ID3D11DeviceContext> m_pContext;
    ComPtr<IDXGISwapChain> m_pSwapChain;

    ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer;
    D3D11_TEXTURE2D_DESC m_BackBufferDesc;
    
    ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
    ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
    D3D11_VIEWPORT m_ViewPort;
    D3D_FEATURE_LEVEL m_FeatureLevel;

    //Window Parameters
    HWND m_hWnd;

    //Graphics Parameters
    UINT m_FrameRate;
    bool m_bIsFullScreen;
    /*bool m_bDepthStencilEnabled;
    bool m_bMultisamplingEnabled;*/

    UINT m_MSAACount;
    UINT m_MSAAQuality;

    UINT m_ClientWidth;
    UINT m_ClientHeight;
    UINT m_AspectRatio;

    //Graphics Flags
    bool m_bEnable4xMSAA = true;
    bool m_bEnableDepthStencil = true;

    //Singleton Instance
    static D3D11_Graphics* m_Instance;
};