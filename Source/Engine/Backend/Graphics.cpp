//Ewan Burnett 2021
//DirectX 11 Graphics Backend

#include "Graphics.h"

D3D11_Graphics* D3D11_Graphics::m_Instance = nullptr;


D3D11_Graphics::D3D11_Graphics(HWND &hWnd, UINT width, UINT height)
{
    assert(m_Instance == nullptr);
    m_Instance = this;

    m_hWnd = hWnd;
    m_ClientWidth = width;
    m_ClientHeight = height;

    m_bEnable4xMSAA = true;
    m_bEnableDepthStencil = true;

    m_FrameRate = 60;

    m_MSAACount = 4;
    m_MSAAQuality = 1;

    //TODO: Replace with Debug layer
    if (!Init()) {
        MessageBox(m_hWnd, L"Error:\nD3D11 Graphics Initialization Failed", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
        PostQuitMessage(0xdeadbeef);
    }
    
}

D3D11_Graphics::~D3D11_Graphics()
{
    //TODO: Convert everything to use WRL::COMPTR 
    /*m_pRenderTargetView->Release();
    m_pDepthStencilView->Release();*/
    //m_pSwapChain->Release();
    if (m_pSwapChain != nullptr) {
       // m_pSwapChain->Release();
    }

    //DEBUG Report any live objects after we've cleaned up
#if defined(DEBUG) | defined (_DEBUG)
    ID3D11Debug* d3dDebug;
    HRESULT hr = m_pDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&d3dDebug));
    if (SUCCEEDED(hr)) {
        hr = d3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
    }
    if (d3dDebug != nullptr) {
        d3dDebug->Release();
    }
   
#endif

    /*if (m_pDevice.Get() != nullptr) {
        m_pDevice->Release();
    }*/
}

bool D3D11_Graphics::Init()
{
    //HRESULT used for error checking
    HRESULT hr;

    //Create the Device
    UINT createDeviceFlags = 0;
#if defined(DEBUG) | defined(_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_0
    };

    hr = D3D11CreateDevice(
        0,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        createDeviceFlags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        m_pDevice.GetAddressOf(),
        &m_FeatureLevel,
        m_pContext.GetAddressOf()
    );

    if (FAILED(hr)) {
        MessageBox(m_hWnd, L"Error:\nD3D11 Device Creation Failed", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
        return false;
    }
    
    
    //Check device for 4xMSAA support. If it is not supported, then D3D11 is not supported.
    m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_MSAAQuality);

    //TODO: Replace with Debug layer
    if (m_MSAAQuality <= 0) {
        MessageBox(m_hWnd, L"Error:\n4x MSAA is not supported by the device.", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
        return false;
    }

    //m_pDevice->Release();

    //Create the SwapChain
    //CreateSwapChain();
    
    //Swap Chain Buffer Desc
    DXGI_MODE_DESC bd = { 0 };
    bd.Width = m_ClientWidth;
    bd.Height = m_ClientHeight;
    bd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    bd.RefreshRate.Numerator = m_FrameRate;
    bd.RefreshRate.Denominator = 1;
    bd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    bd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    DXGI_SWAP_CHAIN_DESC sd = { 0 };
    sd.BufferDesc = bd;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = m_hWnd;
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;
    if (m_bEnable4xMSAA) {
        sd.SampleDesc.Count = m_MSAACount;
        sd.SampleDesc.Quality = m_MSAAQuality - 1;
    }
    else {
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
    }

    //Swap Chain Creation
    IDXGIDevice* dxgiDevice = 0;
    hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    //TODO: Replace with Debug layer
    if (FAILED(hr)) {
        MessageBox(m_hWnd, L"Error:\nFailed to query device interface", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
        return S_FALSE;
    }

    IDXGIAdapter* dxgiAdapter = 0;
    hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

    //TODO: Replace with Debug layer
    if (FAILED(hr)) {
        MessageBox(m_hWnd, L"Error:\nFailed to query adapter parent interface", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
        return false;
    }

    IDXGIFactory* dxgiFactory = 0;
    hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

    //TODO: Replace with Debug layer
    if (FAILED(hr)) {
        MessageBox(m_hWnd, L"Error:\nfailed to query factory parent interface", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
        return false;
    }

    hr = dxgiFactory->CreateSwapChain(dxgiDevice, &sd, m_pSwapChain.ReleaseAndGetAddressOf());

    //TODO: Replace with Debug layer
    if (FAILED(hr)) {
        MessageBox(m_hWnd, L"Error:\nFailed to create Swapchain.", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
        return false;
    }

    dxgiDevice->Release();
    dxgiAdapter->Release();
    dxgiFactory->Release();
    

    //TODO: Add HR checks (? or take some out)
    ID3D11Texture2D* backBuffer;
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    backBuffer->GetDesc(&m_BackBufferDesc);

    hr = m_pDevice->CreateRenderTargetView(backBuffer, nullptr, m_pRenderTargetView.ReleaseAndGetAddressOf());

    //TODO: Replace with Debug layer
    if (FAILED(hr)) {
        MessageBox(m_hWnd, L"Error:\nFailed to create Render Target View.", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
        return false;
    }

    backBuffer->Release();
    //m_pSwapChain->Release();
    //m_pDevice->Release();

    if (m_bEnableDepthStencil == true) {

        //Depth-Stencil Buffer Creation
        D3D11_TEXTURE2D_DESC dsd = { 0 };
        dsd.Width = m_ClientWidth;
        dsd.Height = m_ClientHeight;
        dsd.MipLevels = 1;
        dsd.ArraySize = 1;
        dsd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

        if (m_bEnable4xMSAA) {
            dsd.SampleDesc.Count = m_MSAACount;
            dsd.SampleDesc.Quality = m_MSAAQuality - 1;
        }
        else {
            dsd.SampleDesc.Count = 1;
            dsd.SampleDesc.Quality = 0;
        }

        dsd.Usage = D3D11_USAGE_DEFAULT;
        dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

        ID3D11Texture2D* depthStencilBuffer;
        hr = m_pDevice->CreateTexture2D(&dsd, nullptr, &depthStencilBuffer);

        //TODO: Replace with Debug layer
        if (FAILED(hr)) {
            MessageBox(m_hWnd, L"Error:\nDepth Stencil Buffer Texture Creation Failed", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
            return false;
        }


        D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
        dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
        dsvd.Texture2D.MipSlice = 0;
        dsvd.Flags = 0;

        hr = m_pDevice->CreateDepthStencilView(depthStencilBuffer, &dsvd, m_pDepthStencilView.GetAddressOf());
             
        //TODO: Replace with Debug layer
        if (FAILED(hr)) {
            MessageBox(m_hWnd, L"Error:\nDepth Stencil View Creation Failed", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
            return false;
        }

        depthStencilBuffer->Release();
    }

    //Bind our views to the Output Merger
    m_pContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
    

    //Setting the Viewport
    
    m_ViewPort.TopLeftX = 0.0f;
    m_ViewPort.TopLeftY = 0.0f;
    m_ViewPort.Width = static_cast<float>(m_ClientWidth);
    m_ViewPort.Height = static_cast<float>(m_ClientHeight);
    m_ViewPort.MinDepth = 0.0f;
    m_ViewPort.MaxDepth = 1.0f;

    m_pContext->RSSetViewports(1, &m_ViewPort);

    //TODO: Compile Shaders 
    //TODO: Add support for window resizing (Recreate swapchain)
    return true;
}

void D3D11_Graphics::Clear(float r, float g, float b, float a)
{
    const float clr[4] = { r, g, b, a };
    m_pContext->ClearRenderTargetView(m_pRenderTargetView.Get(), clr);
    m_pContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);    
}

void D3D11_Graphics::SetFramerate(int fps)
{
    //TODO: Recreate the swapchain, with the new Framerate.
    if (fps > 0) {
        m_FrameRate = fps;
        //Init();
    }
}

ID3D11DeviceContext* D3D11_Graphics::Context()
{
    return m_pContext.Get();
}

ID3D11Device* D3D11_Graphics::Device()
{
    return m_pDevice.Get();
}

IDXGISwapChain* D3D11_Graphics::Swapchain()
{
    return m_pSwapChain.Get();
}

HRESULT D3D11_Graphics::CreateSwapChain()
{
    //TODO: Encapsulate SwapChain creation, and add Resize support
    //HRESULT hr;

    ////Swap Chain Buffer Desc
    //DXGI_MODE_DESC bd = { 0 };
    //bd.Width = m_ClientWidth;
    //bd.Height = m_ClientHeight;
    //bd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //bd.RefreshRate.Numerator = m_FrameRate;
    //bd.RefreshRate.Denominator = 1;
    //bd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    //bd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    //DXGI_SWAP_CHAIN_DESC sd = { 0 };
    //sd.BufferDesc = bd;
    //sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    //sd.BufferCount = 1;
    //sd.OutputWindow = m_hWnd;
    //sd.Windowed = true;
    //sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    //sd.Flags = 0;
    //if (m_bEnable4xMSAA) {
    //    sd.SampleDesc.Count = m_MSAACount;
    //    sd.SampleDesc.Quality = m_MSAAQuality - 1;
    //}
    //else {
    //    sd.SampleDesc.Count = 1;
    //    sd.SampleDesc.Quality = 0;
    //}

    ////Swap Chain Creation
    //IDXGIDevice* dxgiDevice = 0;
    //hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    //if (FAILED(hr)) {
    //    MessageBox(m_hWnd, L"Error:\nFailed to query device interface", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
    //    return S_FALSE;
    //}

    //IDXGIAdapter* dxgiAdapter = 0;
    //hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
    //if (FAILED(hr)) {
    //    MessageBox(m_hWnd, L"Error:\nFailed to query adapter parent interface", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
    //    return S_FALSE;
    //}

    //IDXGIFactory* dxgiFactory = 0;
    //hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
    //if (FAILED(hr)) {
    //    MessageBox(m_hWnd, L"Error:\nfailed to query factory parent interface", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
    //    return S_FALSE;
    //}

    //hr = dxgiFactory->CreateSwapChain(dxgiDevice, &sd, m_pSwapChain.ReleaseAndGetAddressOf());
    //if (FAILED(hr)) {
    //    MessageBox(m_hWnd, L"Error:\nFailed to create Swapchain.", L"Error: D3D11 Initialization Failed", MB_OK | MB_ICONERROR);
    //    return S_FALSE;
    //}

    //dxgiDevice->Release();
    //dxgiAdapter->Release();
    //dxgiFactory->Release();

    return S_OK;
}

