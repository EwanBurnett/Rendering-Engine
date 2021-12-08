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
#include "../Utils/Model.h"
#include <memory>


struct Vertex {
    Vertex(DirectX::XMFLOAT3 Position, DirectX::XMFLOAT4 Color) : position(Position), color(Color){}

    DirectX::XMFLOAT3 position;
    float pad = 1.0f;
    DirectX::XMFLOAT4 color; 
};

namespace Engine {
    class ModelComponent : public GameComponent {
    public:
        ModelComponent(D3D11_Graphics* gfx, Camera* cam);
        ~ModelComponent();

        virtual void CreateBuffers();

        void Update(float dt) override;
        void Draw(float dt) override;
            
        void Reset();

        void SetScale(float x = 1.0f, float y = 1.0f, float z = 1.0f);
        void SetRotation(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        void SetTranslation(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        void SetOrigin(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    protected:
        XMFLOAT3 m_Scale;
        XMFLOAT3 m_Rotation;
        XMFLOAT3 m_Translation;
        XMFLOAT3 m_Origin;

    //private:

        std::unique_ptr<Model> m_Model;

        ComPtr<ID3D11Device> m_pDevice;
        ComPtr<ID3D11DeviceContext> m_pContext;

        ComPtr<ID3DX11Effect> m_Effect;
        ComPtr<ID3DX11EffectTechnique> m_Technique;
        ComPtr<ID3DX11EffectPass> m_Pass;
        ComPtr<ID3DX11EffectMatrixVariable> m_WVPVar;
        
        UINT m_IndexCount;
        ComPtr<ID3D11InputLayout> m_InputLayout;
        ComPtr<ID3D11Buffer> m_VertexBuffer;
        ComPtr<ID3D11Buffer> m_IndexBuffer;

        Camera* m_Camera;
        DirectX::XMFLOAT4X4 m_WorldMatrix;
    };
}
