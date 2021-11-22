//Ewan Burnett 2021
//Text Component - A Debug Component, displaying
//any input text. 

#pragma once
#include "../Components/GameComponent.h"
#include "../Backend/Graphics.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <sstream>


namespace DirectX {
    class SpriteBatch;
    class SpriteFont;
}

namespace Engine {
    class TextComponent : public Engine::GameComponent {
    public:
        TextComponent(D3D11_Graphics* gfx);
        ~TextComponent();

        void SetPosition(float x, float y);
        XMFLOAT2& TextPosition();

        void SetText(std::string text);
        void SetColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

        void Init() override;
        void Update(float dt) override;
        void Draw(float dt) override;

    protected:
        std::wstring m_Font;
        XMVECTORF32 m_TextColor;
        XMFLOAT2 m_TextPos;
        std::string m_TextLabel;

    private:
        SpriteBatch* m_SpriteBatch;
        SpriteFont* m_SpriteFont;
              
        D3D11_Graphics* m_Graphics;

        ComPtr<ID3D11RasterizerState> m_prevRastState;
        ComPtr<ID3D11BlendState> m_prevBlendState;
        ComPtr<ID3D11DepthStencilState> m_prevDSState;

        FLOAT* blendFactor = new FLOAT[4];
        UINT sampleMask;
        UINT stencilRef;
    };
}

inline Engine::TextComponent::TextComponent(D3D11_Graphics* gfx) :
    m_SpriteBatch(nullptr), m_SpriteFont(nullptr)
{
    //TODO: Load default font from a Resource file instead
    m_Font = L"..\\..\\Resources\\Fonts\\Arial_14_Regular.spritefont";
    m_TextColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    m_Graphics = gfx;
    SetPosition(0, 0);
    SetText("Default Text");
}


inline Engine::TextComponent::~TextComponent()
{
    delete(m_SpriteBatch);
    delete(m_SpriteFont);

    delete(blendFactor);
    /*if (prevRastState != nullptr) {
        prevRastState->Release();
    }
    if (prevBlendState != nullptr) {
        prevBlendState->Release();
    }
    if (prevDSState != nullptr) {
        prevDSState->Release();
    }*/
}

inline void Engine::TextComponent::SetPosition(float x, float y)
{
    m_TextPos.x = x;
    m_TextPos.y = y;
}

inline XMFLOAT2& Engine::TextComponent::TextPosition()
{
    return m_TextPos;
}

inline void Engine::TextComponent::SetText(std::string text)
{
    m_TextLabel = text.c_str();
}

inline void Engine::TextComponent::SetColor(float r, float g, float b, float a)
{
    m_TextColor = { r, g, b, a };
}

inline void Engine::TextComponent::Init()
{
    m_SpriteBatch = new SpriteBatch(m_Graphics->Context().Get());
    m_SpriteFont = new SpriteFont(m_Graphics->Device().Get(), m_Font.c_str());
}

inline void Engine::TextComponent::Update(float dt)
{
   
}


inline void Engine::TextComponent::Draw(float dt)
{
    //Spritebatch messes with our render states, so cache the current ones before drawing, and restore them after
    m_Graphics->Context()->RSGetState(&m_prevRastState);
    m_Graphics->Context()->OMGetBlendState(&m_prevBlendState, blendFactor, &sampleMask);
    m_Graphics->Context()->OMGetDepthStencilState(&m_prevDSState, &stencilRef);

    m_SpriteBatch->Begin();

    m_SpriteFont->DrawString(m_SpriteBatch, m_TextLabel.c_str(), m_TextPos, m_TextColor);

    m_SpriteBatch->End();
    
    m_Graphics->Context()->OMSetDepthStencilState(m_prevDSState.Get(), stencilRef);
    m_Graphics->Context()->OMSetBlendState(m_prevBlendState.Get(), blendFactor, sampleMask);
    m_Graphics->Context()->RSSetState(m_prevRastState.Get());

}
