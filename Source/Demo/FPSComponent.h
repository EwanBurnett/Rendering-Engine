#pragma once
#include "GameComponent.h"
#include "Graphics.h"
#include "Time.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <sstream>

namespace DirectX {
    class SpriteBatch;
    class SpriteFont;
}

namespace Engine {
    class FPSComponent : public GameComponent {
    public:        
        FPSComponent(Time* itime, D3D11_Graphics* gfx);
        ~FPSComponent();

        XMFLOAT2& TextPosition();
        int FrameRate() const;

        virtual void Init() override;
        virtual void Update(float dt) override;
        virtual void Draw(float dt) override;

    private:
        FPSComponent();
        SpriteBatch* m_SpriteBatch;
        SpriteFont* m_SpriteFont;

        XMFLOAT2 m_TextPos;

        int m_FrameRate;
        Time* m_Time;
        D3D11_Graphics* m_Graphics;

        
    };
}

inline Engine::FPSComponent::FPSComponent(Time* itime, D3D11_Graphics* gfx)
{
    m_Time = itime;
    m_Graphics = gfx;
}

inline Engine::FPSComponent::~FPSComponent()
{
    delete(m_SpriteBatch);
    delete(m_SpriteFont);
    delete(m_Graphics);
    delete(m_Time);
}

inline void Engine::FPSComponent::Init()
{
    m_SpriteBatch = new SpriteBatch(m_Graphics->Context());
    m_SpriteFont = new SpriteFont(m_Graphics->Device(), L"Resources\\Fonts\\Arial_14_Regular.spritefont");
}

inline void Engine::FPSComponent::Update(float dt)
{
    m_FrameRate = 1/m_Time->DeltaTime();
}

inline void Engine::FPSComponent::Draw(float dt)
{
    m_SpriteBatch->Begin();

    std::wostringstream fpsLabel;
    fpsLabel << L"FrameRate: " << m_FrameRate << L"Total Elapsed Time" << m_Time->TotalTime();
    m_SpriteFont->DrawString(m_SpriteBatch, fpsLabel.str().c_str(), m_TextPos);

    m_SpriteBatch->End();
}
