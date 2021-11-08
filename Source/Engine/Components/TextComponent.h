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
    };
}

inline Engine::TextComponent::TextComponent(D3D11_Graphics* gfx) :
    m_SpriteBatch(nullptr), m_SpriteFont(nullptr)
{
    m_Font = L"Resources\\Fonts\\Arial_14_Regular.spritefont";
    m_TextColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    m_Graphics = gfx;
    SetPosition(0, 0);
    SetText("Default Text");
}


inline Engine::TextComponent::~TextComponent()
{
    delete(m_SpriteBatch);
    delete(m_SpriteFont);
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
    m_SpriteBatch = new SpriteBatch(m_Graphics->Context());
    m_SpriteFont = new SpriteFont(m_Graphics->Device(), m_Font.c_str());
}

inline void Engine::TextComponent::Update(float dt)
{
   
}


inline void Engine::TextComponent::Draw(float dt)
{
    m_SpriteBatch->Begin();

    m_SpriteFont->DrawString(m_SpriteBatch, m_TextLabel.c_str(), m_TextPos, m_TextColor);

    m_SpriteBatch->End();

}
