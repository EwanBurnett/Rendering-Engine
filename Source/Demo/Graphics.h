#pragma once
//DirectX11 Graphics Backend
//Ewan Burnett 2021

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
#include <wrl.h>

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

private:
    //D3D11 Pointers
    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pContext;
    ComPtr<IDXGISwapChain> m_pSwapChain;

    ID3D11Texture2D* m_pDepthStencilBuffer;
    D3D11_TEXTURE2D_DESC m_BackBufferDesc;
    
    ID3D11RenderTargetView* m_pRenderTargetView;
    ID3D11DepthStencilView* m_pDepthStencilView;
    D3D_FEATURE_LEVEL m_FeatureLevel;

    //Window Parameters
    HWND m_hWnd;

    //Graphics Parameters
    UINT m_FrameRate;
    bool m_bIsFullScreen;
    bool m_bDepthStencilEnabled;
    bool m_bMultisamplingEnabled;

    UINT m_MSAACount;
    UINT m_MSAAQuality;

    UINT m_ClientWidth;
    UINT m_ClientHeight;
    UINT m_AspectRatio;

};