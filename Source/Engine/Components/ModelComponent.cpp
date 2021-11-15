 #include "ModelComponent.h"
using namespace DirectX;

Engine::ModelComponent::ModelComponent(D3D11_Graphics* gfx, Camera* cam)
{

    XMMATRIX m = XMMatrixRotationRollPitchYaw(15, 45, 30) * XMMatrixTranslation(0, 0, -8);
    XMStoreFloat4x4(&m_WorldMatrix, m);

    UINT shaderFlags = 0;
    //
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
    HRESULT hr = D3DCompileFromFile(L"..\\..\\Resources\\Effects\\BasicEffect.fx", nullptr, nullptr, nullptr, "fx_5_0", shaderFlags, 0, &compiledShader, &errorMessages);
    //D3DCompileFromFile(L"S", nullptr, nullptr, nullptr, "fx_5_0", shaderFlags, 0, &compiledShader, &errorMessages);
    if (FAILED(hr))
    {
        //
    }
    if(errorMessages != nullptr) {
        //Do some error handling
        OutputDebugString((LPCWSTR)errorMessages->GetBufferPointer());
    }

    if (compiledShader != nullptr) {
        hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, m_pDevice, &m_Effect);
    }


    if (FAILED(hr)) {
        //do more error checking
    }

    compiledShader->Release();

    //Retrieving Techniques, passes and variables
    m_Technique = m_Effect->GetTechniqueByName("main11");
    if (m_Technique == nullptr) {
        //More error checking...
    }

    m_Pass = m_Technique->GetPassByName("p0");
    if (m_Pass == nullptr) {
        //TODO: Error Check for Pass
    }

    ID3DX11EffectVariable* var = m_Effect->GetVariableByName("WorldViewProjection");
    if (var == nullptr) {
        //You know the drill
    }

    m_WVPVar = var->AsMatrix();
    if (m_WVPVar->IsValid() == false) {
        //...
    }

    //Create an input layout
    D3DX11_PASS_DESC passDesc;
    m_Pass->GetDesc(&passDesc);

    D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    hr = m_pDevice->CreateInputLayout(inputElementDescriptions, ARRAYSIZE(inputElementDescriptions), passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_InputLayout);
    if (FAILED(hr)) {
        //Whaddya think
    }

    //Create a vertex buffer
    //DEBUG PYRAMID
    Vertex verts[] = {
        //Cube
        {XMFLOAT3(-0.5, -0.75,	-0.5),		XMFLOAT4(1, 1, 1, 1)},		//White		0
        {XMFLOAT3(0.5,	-0.75,	-0.5),		XMFLOAT4(1, 1, 0, 1)},		//Yellow	1
        {XMFLOAT3(0.5,	-0.75,	0.5),		XMFLOAT4(1, 0, 1, 1)},		//Purple	2
        {XMFLOAT3(-0.5,	-0.75,	0.5),		XMFLOAT4(0, 1, 1, 1)},		//Turquoise	3
        {XMFLOAT3(-0.5, 0.75,	-0.5),		XMFLOAT4(1, 0, 0, 1)},		//Red		4
        {XMFLOAT3(0.5,	0.75,	-0.5),		XMFLOAT4(0, 1, 0, 1)},		//Green		5
        {XMFLOAT3(0.5,	0.75,	0.5),		XMFLOAT4(0, 0, 1, 1)},		//Blue		6
        {XMFLOAT3(-0.5,	0.75,	0.5),		XMFLOAT4(0, 0, 0, 1)},		//Black		7
    };

    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
    vertexBufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(verts);
    vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexSubresourceData;
    ZeroMemory(&vertexSubresourceData, sizeof(vertexSubresourceData));
    vertexSubresourceData.pSysMem = verts;

    hr = m_pDevice->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &m_VertexBuffer);
    if (FAILED(hr)) {
        //...
    }
    /*UINT stride = sizeof(Vertex);
    UINT offset = 0;

    m_pContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);*/

    //Index list for our shape
    UINT indices[] = {
        0, 1, 2,	0, 2, 3, //Bottom Face
        0, 4, 5,	0, 5, 1, //Back Face
        1, 5, 6,	1, 6, 2, //Right Face
        2, 6, 7,	2, 7, 3, //Front Face
        3, 7, 4,	3, 4, 0, //Left Face
        4, 6, 5,	4, 7, 6, //Top Face
    };

    //mIndexCount = sizeof(indices);

    //Creating an index buffer Description
    D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = static_cast<UINT>(sizeof(UINT) * std::size(indices));
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    ibd.StructureByteStride = 0;

    //Initializse the index buffer with our data
    D3D11_SUBRESOURCE_DATA iInitData;
    iInitData.pSysMem = indices;

    //Create the buffer
   ID3D11Buffer* mIB;
    m_pDevice->CreateBuffer(&ibd, &iInitData, &mIB);

    //Bind the buffer to the pipeline
    m_pContext->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);


}

void Engine::ModelComponent::Draw(float dt)
{
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pContext->IASetInputLayout(m_InputLayout);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_pContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

    XMMATRIX world = XMLoadFloat4x4(&m_WorldMatrix);
    XMMATRIX wvp = world * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();

    m_WVPVar->SetMatrix(reinterpret_cast<const float*>(&wvp));

    m_Pass->Apply(0, m_pContext);

    
    m_pContext->DrawIndexed(36, 0, 0);
    //m_pContext->Draw(4, 0);
}
