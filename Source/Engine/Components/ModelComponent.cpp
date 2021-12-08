#include "ModelComponent.h"

using namespace DirectX;

Engine::ModelComponent::ModelComponent(D3D11_Graphics* gfx, Camera* cam)
{   

    Reset();

    UINT shaderFlags = 0;
    
    m_pDevice = gfx->Device();
    m_pContext = gfx->Context();

    m_Camera = cam;

#if defined(DEBUG) || defined(_DEBUG)
    shaderFlags |= D3DCOMPILE_DEBUG;
    shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3D10Blob* compiledShader = nullptr;
    ID3D10Blob* errorMessages = nullptr;

    //TODO: Rewrite effects for D3D11, and add to Effects directory
    //TODO: Load from a Resource file instead
    HRESULT hr = D3DCompileFromFile(L"..\\..\\Resources\\Effects\\BasicEffect.fx", nullptr, nullptr, nullptr, "fx_5_0", shaderFlags, 0, &compiledShader, &errorMessages);
    //D3DCompileFromFile(L"S", nullptr, nullptr, nullptr, "fx_5_0", shaderFlags, 0, &compiledShader, &errorMessages);
    if (FAILED(hr))
    {
        //TODO: Do some error handling
    }
    if(errorMessages != nullptr) {
        //TODO: Do some error handling
        OutputDebugString((LPCWSTR)errorMessages->GetBufferPointer());
    }

    if (compiledShader == nullptr) {
        //TODO: Do some error handling
    }

    hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, m_pDevice.Get(), m_Effect.GetAddressOf());

    if (FAILED(hr)) {
        //TODO: Do some error handling
    }

    compiledShader->Release();

    //Retrieving Techniques, passes and variables
    m_Technique = m_Effect->GetTechniqueByName("main11");
    if (m_Technique == nullptr) {
        //TODO: Do some error handling
    }

    m_Pass = m_Technique->GetPassByName("p0");
    if (m_Pass == nullptr) {
        //TODO: Do some error handling
    }

    ID3DX11EffectVariable* var = m_Effect->GetVariableByName("WorldViewProjection");
    if (var == nullptr) {
        //TODO: Do some error handling
    }

    m_WVPVar = var->AsMatrix();
    if (m_WVPVar->IsValid() == false) {
        //TODO: Do some error handling
    }

    var->Release();

    //Create an input layout
    D3DX11_PASS_DESC passDesc;
    m_Pass->GetDesc(&passDesc);

    D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    hr = m_pDevice->CreateInputLayout(inputElementDescriptions, ARRAYSIZE(inputElementDescriptions), passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, m_InputLayout.GetAddressOf());
    if (FAILED(hr)) {
        //TODO: Do some error handling
    }

    std::string a = "D:\\University\\Projects\\Year 2\\Rendering Engine\\Build\\Debug\\Resources\\amber.fbx";
    //model = std::make_unique<Engine::Model>(gfx, "Resources\\Models\\Sphere.obj", true);
    m_Model = std::make_unique<Engine::Model>(gfx, a, true);
    CreateBuffers();

   
}

Engine::ModelComponent::~ModelComponent()
{
    //Release acquired interfaces
    //m_pDevice->Release();
    //m_pContext->Release();

    //m_Effect->Release();
    //m_Technique->Release();
    //m_Pass->Release();
    //m_WVPVar->Release();

    //m_InputLayout->Release();
    //m_VertexBuffer->Release();

}

void Engine::ModelComponent::CreateBuffers()
{
    Mesh* mesh = m_Model->Meshes().at(0);

    const std::vector<XMFLOAT3>& src = mesh->Vertices();
    std::vector<Vertex> verts;

    verts.reserve(src.size());
    
    if (mesh->VertexColours().size() > 0) {
        std::vector<XMFLOAT4>* vertClrs = mesh->VertexColours().at(0);

        if (vertClrs->size() == src.size()) {
            //TODO: Link to debug layer
        }


    }

    m_IndexCount = mesh->Indices().size();


}

void Engine::ModelComponent::Update(float dt)
{
    XMVECTOR scale = XMLoadFloat3(&m_Scale);
    XMVECTOR rotation = XMLoadFloat3(&m_Rotation);
    XMVECTOR translation = XMLoadFloat3(&m_Translation);

    XMMATRIX m = XMMatrixScalingFromVector(scale) * XMMatrixRotationRollPitchYawFromVector(rotation) * XMMatrixTranslationFromVector(translation);
    XMStoreFloat4x4(&m_WorldMatrix, m);
}

void Engine::ModelComponent::Draw(float dt)
{
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pContext->IASetInputLayout(m_InputLayout.Get());

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_pContext->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

    m_pContext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    XMMATRIX world = XMLoadFloat4x4(&m_WorldMatrix);
    XMMATRIX wvp = world * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();

    m_WVPVar->SetMatrix(reinterpret_cast<const float*>(&wvp));

    m_Pass->Apply(0, m_pContext.Get());

    
    m_pContext->DrawIndexed(m_IndexCount, 0, 0);
}

void Engine::ModelComponent::Reset()
{
    XMStoreFloat3(&m_Scale, XMVectorSet(1, 1, 1, 1));
    XMStoreFloat3(&m_Rotation, XMVectorZero());
    XMStoreFloat3(&m_Translation, XMVectorZero());
}

void Engine::ModelComponent::SetScale(float x, float y, float z)
{
    XMStoreFloat3(&m_Scale, XMVectorSet(x, y, z, 1));
}

void Engine::ModelComponent::SetRotation(float x, float y, float z)
{
    XMStoreFloat3(&m_Rotation, XMVectorSet(
        XMConvertToRadians(x), XMConvertToRadians(y), XMConvertToRadians(z), 1));
}

void Engine::ModelComponent::SetTranslation(float x, float y, float z)
{
    XMStoreFloat3(&m_Translation, XMVectorSet(m_Origin.x + x, m_Origin.y + y, m_Origin.z + z, 1));
}

void Engine::ModelComponent::SetOrigin(float x, float y, float z)
{
    XMStoreFloat3(&m_Origin, XMVectorSet(x, y, z, 1));
}
