#include "PrimitiveModelComponent.h"

Engine::Primitive::Primitive(D3D11_Graphics* gfx, Camera* cam) : ModelComponent(gfx, cam)
{
    
}

void Engine::Primitive::CreateBuffers()
{
    //Create a vertex buffer
    //DEBUG PYRAMID
    Vertex verts[] = {
        //Cube
        {XMFLOAT3(-0.5, -0.5,	-0.5),		XMFLOAT4(1, 1, 1, 1)},		//White		0
        {XMFLOAT3(0.5,	-0.5,	-0.5),		XMFLOAT4(1, 1, 0, 1)},		//Yellow	1
        {XMFLOAT3(0.5,	-0.5,	0.5),		XMFLOAT4(1, 0, 1, 1)},		//Purple	2
        {XMFLOAT3(-0.5,	-0.5,	0.5),		XMFLOAT4(0, 1, 1, 1)},		//Turquoise	3
        {XMFLOAT3(-0.5, 0.5,	-0.5),		XMFLOAT4(1, 0, 0, 1)},		//Red		4
        {XMFLOAT3(0.5,	0.5,	-0.5),		XMFLOAT4(0, 1, 0, 1)},		//Green		5
        {XMFLOAT3(0.5,	0.5,	0.5),		XMFLOAT4(0, 0, 1, 1)},		//Blue		6
        {XMFLOAT3(-0.5,	0.5,	0.5),		XMFLOAT4(0, 0, 0, 1)},		//Black		7
    };

    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
    vertexBufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(verts);
    vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexSubresourceData;
    ZeroMemory(&vertexSubresourceData, sizeof(vertexSubresourceData));
    vertexSubresourceData.pSysMem = verts;

    HRESULT hr = m_pDevice->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, m_VertexBuffer.GetAddressOf());
    if (FAILED(hr)) {
        //TODO: Do some error handling
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


    m_IndexCount = sizeof(indices);

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

    //Create the index buffer
    m_pDevice->CreateBuffer(&ibd, &iInitData, m_IndexBuffer.GetAddressOf());
}
