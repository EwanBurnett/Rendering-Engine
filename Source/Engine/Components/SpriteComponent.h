//Ewan Burnett 2021
//Sprite Component - A Debug Component, displaying
//any input text. 

#pragma once
#include "../Components/GameComponent.h"
#include "../Backend/Graphics.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <sstream>
#include <DDSTextureLoader.h>


namespace DirectX {
    class SpriteBatch;
    class SpriteFont;
}

namespace Engine {
    class SpriteComponent : public Engine::GameComponent {
    public:
        SpriteComponent(D3D11_Graphics* gfx);
        ~SpriteComponent();

        void SetPosition(float x, float y);
        XMFLOAT2& SpritePosition();

        void SetSprite(std::wstring text);
        void SetColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

        void Init() override;
        void Update(float dt) override;
        void Draw(float dt) override;

    protected:
        std::wstring m_SpritePath;
        XMVECTORF32 m_SpriteColor;
        XMFLOAT2 m_SpritePos;
        RECT m_SpriteRect;
        XMFLOAT2 m_SpriteOrigin;
        float m_SpriteScale;
        SpriteEffects m_SpriteEffect;
        float m_SpriteDepth;

    private:
        SpriteBatch* m_SpriteBatch;
        ID3D11ShaderResourceView* m_Resource;
        D3D11_Graphics* m_Graphics;
        
    };
}

inline Engine::SpriteComponent::SpriteComponent(D3D11_Graphics* gfx) :
    m_SpriteBatch(nullptr)
{
    
    m_SpriteColor = { 1.0f, 1.0f, 1.0f, 0.2f };
    m_SpriteEffect = SpriteEffects_FlipHorizontally;
    m_SpriteDepth = 0.0f;
    m_SpriteOrigin = XMFLOAT2(0, 0);
    m_SpriteScale = 1.0f;

    m_SpriteRect = { 0, 0, 512, 256 };
    m_Graphics = gfx;
    SetPosition(0, 0);
    SetSprite(L"..\\..\\Resources\\Textures\\DefaultTexture.dds");
}


inline Engine::SpriteComponent::~SpriteComponent()
{
    m_Resource->Release();
    delete(m_SpriteBatch);
}

inline void Engine::SpriteComponent::SetPosition(float x, float y)
{
    m_SpritePos.x = x;
    m_SpritePos.y = y;
}

inline XMFLOAT2& Engine::SpriteComponent::SpritePosition()
{
    return m_SpritePos;
}

inline void Engine::SpriteComponent::SetSprite(std::wstring filePath)
{

    m_SpritePath = filePath;
    //TODO: Hook in Resource Manager
    HRESULT hr = CreateDDSTextureFromFile(m_Graphics->Device(), m_SpritePath.c_str(), nullptr, &m_Resource);
    if (FAILED(hr)) {
        OutputDebugString(L"Unable to load texture");
    }
}

inline void Engine::SpriteComponent::SetColor(float r, float g, float b, float a)
{
    m_SpriteColor = { r, g, b, a };
}

inline void Engine::SpriteComponent::Init()
{
    m_SpriteBatch = new SpriteBatch(m_Graphics->Context());
}

inline void Engine::SpriteComponent::Update(float dt)
{

}


inline void Engine::SpriteComponent::Draw(float dt)
{
    m_SpriteBatch->Begin();

    //Draw the whole sprite, if size is not specified
    //m_SpriteBatch->Draw(m_Resource, m_SpritePos, m_SpriteColor);

    //Else, Draw a subrect of the sprite
    m_SpriteBatch->Draw(m_Resource, m_SpritePos, &m_SpriteRect, m_SpriteColor, 0.0f, m_SpriteOrigin, m_SpriteScale, m_SpriteEffect, m_SpriteDepth);

    m_SpriteBatch->End();

}
