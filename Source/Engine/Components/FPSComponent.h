//Ewan Burnett 2021
//FPS Component - A Debug Component which displays the
//Framerate, Frame time and Delta Time 

#pragma once
#include "../Components/TextComponent.h"
#include "../Utils/Time.h"
#include <iomanip>


namespace Engine {
    class FPSComponent : public Engine::TextComponent {
    public:
        FPSComponent(Time* time, D3D11_Graphics* gfx);

        void Update(float dt) override;

    private:
        int m_FrameRate;
        Time* m_Time;
        D3D11_Graphics* m_Graphics;

    };
}

inline Engine::FPSComponent::FPSComponent(Time* time, D3D11_Graphics* gfx) : TextComponent(gfx)
{
    m_FrameRate = 0;

    m_Time = time;
    m_Graphics = gfx;

    m_TextPos = XMFLOAT2(10, 10);
} 


inline void Engine::FPSComponent::Update(float dt)
{
    m_FrameRate = static_cast<int>(1/m_Time->DeltaTime());
    
    m_TextLabel = "Debug Frame Statistics \nFrameRate: " + std::to_string(m_FrameRate) + "\nCurrent Frame Time: " + std::to_string(m_Time->DeltaTime()) + "\nTotal Elapsed Time: " + std::to_string(m_Time->TotalTime());
}
