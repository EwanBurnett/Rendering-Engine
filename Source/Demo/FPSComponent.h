#pragma once
#include <Components/GameComponent.h>
#include <Utils/Time.h>
#include <Backend/Graphics.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <sstream>


namespace DirectX {
    class SpriteBatch;
    class SpriteFont;
}

namespace Engine {
    class FPSComponent : public Engine::GameComponent {
    public:        
        FPSComponent(Time* itime, D3D11_Graphics* gfx);
        ~FPSComponent();

        XMFLOAT2& TextPosition();
        int FrameRate() const;

        void Init() override;
        void Update(float dt) override;
        void Draw(float dt) override;

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

    m_TextPos = XMFLOAT2(10, 10);
}

inline Engine::FPSComponent::~FPSComponent()
{
    delete(m_SpriteBatch);
    delete(m_SpriteFont);
    //delete(m_Graphics);
    //delete(m_Time);
}

inline XMFLOAT2& Engine::FPSComponent::TextPosition()
{
    return m_TextPos;
}

inline void Engine::FPSComponent::Init()
{
    //SetCurrentDirectory(L"\\Resources\\Fonts\\");
    
    m_SpriteBatch = new SpriteBatch(m_Graphics->Context());
    m_SpriteFont = new SpriteFont(m_Graphics->Device(), L"Resources\\Fonts\\Arial_14_Regular.spritefont");
}

inline void Engine::FPSComponent::Update(float dt)
{
    m_FrameRate = static_cast<int>(1/m_Time->DeltaTime());
}

inline void Engine::FPSComponent::Draw(float dt)
{
    m_SpriteBatch->Begin();

    std::wostringstream fpsLabel;
    fpsLabel << L"FrameRate: " << m_FrameRate << L" Current Frame Time: " << m_Time->DeltaTime() <<  L" Total Elapsed Time: " << m_Time->TotalTime() << std::endl;
    
    m_SpriteFont->DrawString(m_SpriteBatch, fpsLabel.str().c_str(), m_TextPos, DirectX::Colors::AliceBlue);


    m_SpriteBatch->End();

}
