#include "ModelComponent.h"
#include "../Utils/Random.h"

using namespace DirectX;

Engine::ModelComponent::ModelComponent(D3D11_Graphics* gfx, Camera* cam)
{   

    Reset();

    UINT shaderFlags = 0;
    
    m_pDevice = gfx->Device();
    m_pContext = gfx->Context();
    m_pGfx = gfx;
    m_Camera = cam;

#if defined(DEBUG) || defined(_DEBUG)
    shaderFlags |= D3DCOMPILE_DEBUG;
    shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3D10Blob* compiledShader = nullptr;
    ID3D10Blob* errorMessages = nullptr;

    //TODO: Load from a Resource file instead
    //TODO: Upgrade to use m_EffectPath variable
    HRESULT hr = D3DCompileFromFile(L"..\\..\\Resources\\Effects\\TextureMapping.fx", nullptr, nullptr, nullptr, "fx_5_0", shaderFlags, 0, &compiledShader, &errorMessages);
    if (FAILED(hr))
    {
        //TODO: Do some error handling
        OutputDebugStringA("Unable to compile shader from file.\n");
    }
    if(errorMessages != nullptr) {
        //TODO: Do some error handling
        OutputDebugStringA("Shader Compilation Errors found - \n");
        OutputDebugString((LPCWSTR)errorMessages->GetBufferPointer());
    }

    if (compiledShader == nullptr) {
        //TODO: Do some error handling
        OutputDebugStringA("Compiled shader is invalid.\n");
    }

    hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, m_pDevice.Get(), m_Effect.GetAddressOf());

    if (FAILED(hr)) {
        //TODO: Do some error handling
        OutputDebugStringA("Error in creating effect.\n");
    }

    compiledShader->Release();

    //Retrieving Techniques, passes and variables
    m_Technique = m_Effect->GetTechniqueByName("main11");
    if (m_Technique == nullptr) {
        //TODO: Do some error handling
        OutputDebugStringA("Unable to retrieve technique.\n");
    }

    m_Pass = m_Technique->GetPassByName("p0");
    if (m_Pass == nullptr) {
        //TODO: Do some error handling
        OutputDebugStringA("Unable to retrieve pass.\n");
    }

    ID3DX11EffectVariable* var = m_Effect->GetVariableByName("WorldViewProj");
    if (var == nullptr) {
        //TODO: Do some error handling
        OutputDebugStringA("Unable to retrieve Variable WorldViewProj.\n");
    }

    m_WVPVar = var->AsMatrix();
    if (m_WVPVar->IsValid() == false) {
        //TODO: Do some error handling
    }

    var = m_Effect->GetVariableByName("ColorTexture");
    if (var == nullptr) {
        //TODO: Do some error handling
    }

    m_ColorTextureVar = var->AsShaderResource();
    if (m_ColorTextureVar->IsValid() == false) {
        //TODO: Do some error handling
    }


    var->Release();

    //Create an input layout
    D3DX11_PASS_DESC passDesc;
    m_Pass->GetDesc(&passDesc);

    D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    hr = m_pDevice->CreateInputLayout(inputElementDescriptions, ARRAYSIZE(inputElementDescriptions), passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, m_InputLayout.GetAddressOf());
    if (FAILED(hr)) {
        //TODO: Do some error handling
    }

    
}

Engine::ModelComponent::~ModelComponent()
{
}

void Engine::ModelComponent::CreateBuffers()
{
    static int offset = 0;

    std::vector<Vertex> verts;
    std::vector<UINT> indices;

    for (size_t t = 0; t < (m_Model->Meshes().size()); t++) {
    //for (size_t t = 0; t < 2; t++) {
        Mesh* mesh = m_Model->Meshes().at(t);

        //Create the vertex buffer
        //(Position, Colour, Normal)
        //TODO: add support for multiple vertex colour meshes
        const std::vector<XMFLOAT3>& vertPos = mesh->Vertices();
        std::vector<std::vector<XMFLOAT4>*> vertClrs = mesh->VertexColours();
        std::vector<std::vector<XMFLOAT3>*> vertTexCoords = mesh->TexCoords();

        
        //verts.reserve(vertPos.size());
        offset += vertPos.size();

        //TODO: assert whether each element == size of vertex positions

        //Append the positions to the vertex buffer
        for (size_t i = 0; i < vertPos.size(); i++) {
            Vertex v;

            v.position = vertPos.at(i);

            if (vertClrs.size() > 0) {
                //XMFLOAT4 color = vertClrs.at(0)->at(i);
                v.color = vertClrs.at(0)->at(i);
            }
#if defined(DEBUG) | defined(_DEBUG)
            //DEBUG - Set a random vertex colour (so models can at least be previewed)
            else {
                RNG rng;
                rng.Seed(0);
                v.color.x = (float)(rng.RandInt(255)) / 255.0f;
                v.color.y = (float)(rng.RandInt(255)) / 255.0f;
                v.color.z = (float)(rng.RandInt(255)) / 255.0f;
                v.color.w = 1.0f;
            }
#endif
            if (vertTexCoords.size() > 0) {
                v.texCoords.x = vertTexCoords.at(0)->at(i).x;
                v.texCoords.y = vertTexCoords.at(0)->at(i).y;
            }

            verts.push_back(v);
        }

        m_IndexCount += mesh->Indices().size();
        
        for (int i = 0; i < mesh->Indices().size(); i++) {
            indices.push_back(mesh->Indices().at(i));
        }
    }

    OutputDebugStringA("Binding Model Buffers\n");
    //Bind the vertex buffer
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
    vertexBufferDesc.ByteWidth = sizeof(Vertex) * verts.size();
    vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexSubresourceData;
    ZeroMemory(&vertexSubresourceData, sizeof(vertexSubresourceData));

    if (verts.size() <= 0) {
        assert(false);
    }

    vertexSubresourceData.pSysMem = &verts[0];
    HRESULT hr = m_pDevice->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, m_VertexBuffer.GetAddressOf());
    if (FAILED(hr)) {
        //TODO: Do some error handling
        OutputDebugStringA("Something Went Wrong");
    }


    //Create and bind the index buffer
    

    //Creating an index buffer Description
    D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = static_cast<UINT>(sizeof(UINT) * indices.size());
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    ibd.StructureByteStride = 0;

    //Initializse the index buffer with our data
    D3D11_SUBRESOURCE_DATA iInitData;
    iInitData.pSysMem = &indices[0];

    //Create the index buffer
    m_pDevice->CreateBuffer(&ibd, &iInitData, m_IndexBuffer.GetAddressOf());


    OutputDebugStringA("Model Loaded\n");

}

void Engine::ModelComponent::Init()
{
    //Load the model
    m_Model = std::make_unique<Engine::Model>(m_pGfx, m_ModelPath, true);

    CreateBuffers();

    //Load the texture
    std::wstring textureName;
    textureName = m_TexturePaths.at(0);

    HRESULT hr = DirectX::CreateWICTextureFromFile(m_pDevice.Get(), m_pContext.Get(), textureName.c_str(), nullptr, &m_TextureView);
    if (FAILED(hr)) {
        //TODO: Do some error handling
        OutputDebugStringA((LPCSTR)textureName.c_str());
        OutputDebugStringA("Unable to load specified texture. Attempting to use default texture instead.");

        //If the original texture can't be loaded, use the default texture instead
        hr = DirectX::CreateDDSTextureFromFile(m_pDevice.Get(), m_pContext.Get(), L"D:\\University\\Projects\\Year 2\\Rendering Engine\\Build\\Debug\\Resources\\Textures\\DefaultTexture.dds", nullptr, &m_TextureView);

        if (FAILED(hr)) {
            OutputDebugStringA("Unable to load default texture.");
        }
    }

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

    m_ColorTextureVar->SetResource(m_TextureView.Get());

    m_Pass->Apply(0, m_pContext.Get());

    //m_pContext->Draw(1400, 0);
    m_pContext->DrawIndexed(m_IndexCount, 0, 0);
}

void Engine::ModelComponent::SetModelPath(std::string path)
{
    m_ModelPath = path;
}

void Engine::ModelComponent::SetTexture(std::wstring path, int slot)
{
    m_TexturePaths.insert(m_TexturePaths.begin() + slot, path);
}

void Engine::ModelComponent::Reset()
{
    XMStoreFloat3(&m_Scale, XMVectorSet(1, 1, 1, 1));
    XMStoreFloat3(&m_Rotation, XMVectorZero());
    XMStoreFloat3(&m_Translation, XMVectorZero());
}

UINT Engine::ModelComponent::FaceCount()
{
    //Compute the total number of faces for this model.
    int faces = 0;

    for (auto& mesh : m_Model->Meshes()) {
        faces += mesh->FaceCount();
    }

    return faces;
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
