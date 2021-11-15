//Ewan Burnett 2021
//Model Component - this component acts as a base for any
//components which require a 3D Model to be represented on screen

#pragma once
#include <DirectXMath.h>
#include "GameComponent.h"
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dx11effect.h>
#include "..\Backend\Graphics.h"
#include "Camera.h"

typedef struct Vertex {
    Vertex(DirectX::XMFLOAT3 Position, DirectX::XMFLOAT4 Color) : position(Position), color(Color){}

    DirectX::XMFLOAT3 position;
    float pad = 1.0f;
    DirectX::XMFLOAT4 color; 
};

namespace Engine {
    class ModelComponent : public GameComponent {
    public:
        ModelComponent(D3D11_Graphics* gfx, Camera* cam);

        void Draw(float dt) override;
    private:
        ID3D11Device* m_pDevice;
        ID3D11DeviceContext* m_pContext;

        ID3DX11Effect* m_Effect;
        ID3DX11EffectTechnique* m_Technique;
        ID3DX11EffectPass* m_Pass;
        ID3DX11EffectMatrixVariable* m_WVPVar;

        ID3D11InputLayout* m_InputLayout;
        ID3D11Buffer* m_VertexBuffer;

        Camera* m_Camera;
        DirectX::XMFLOAT4X4 m_WorldMatrix;
    };
}
