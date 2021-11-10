#include "Game.h"
#include <Components/FPSComponent.h>
#include <Components/TextComponent.h>
#include <iostream>

Engine::TextComponent* textComponent;
Engine::TextComponent* keyboardView;
int frameLimitSwitch = 0;

//Init is called when the application is started.
void Game::Init()
{
    textComponent = new Engine::TextComponent(m_Graphics.get());
    textComponent->SetPosition(10, 10);
    textComponent->SetText("Default Rendering Demo\nEwan Burnett [2021]\nA simple demo, demonstrating rendered text.\nFramerate Controls:\n    F1 - uncapped\n    F2 - 15 FPS\n    F3 - 30 FPS\n    F4 - 60 FPS");
    m_Components.push_back(textComponent);

    Engine::FPSComponent* fpsComponent = new Engine::FPSComponent(&m_Time, m_Graphics.get());
    fpsComponent->TextPosition() = DirectX::XMFLOAT2(400, 10);
    fpsComponent->SetColor(0, 1, 0.25);
    m_Components.push_back(fpsComponent);

    keyboardView = new Engine::TextComponent(m_Graphics.get());
    keyboardView->SetPosition(10, 660);
    keyboardView->SetColor(0.05, 0.2, 1.0, 1.0);
    m_Components.push_back(keyboardView);

    Engine::TextComponent* warning = new  Engine::TextComponent(m_Graphics.get());
    warning->SetText("DON'T EVEN THINK ABOUT MOVING ONTO\nRENDERING BEFORE YOU FULLY IMPLEMENT AND TEST\nALL THIS BACKEND STUFF!!!\n- Keyboard Input\n- Mouse Input\n- Building Fonts\n- Object Pooling\n- Camera Matrices\n- Framerate Limiting\n- Game Objects\n- Byte Alignment\n- OPTIMISATIONS\n- Warnings\n- Memory Leaks\n- COM Pointers\n- Sprite Component\n- COMMENTING\n- ARCHITECTURAL DESIGN DOCUMENT!!!!!!!!!\n- ...and tidying up :D\nHave Fun <3");
    warning->SetColor(1, 0, 0.05, 1.0f);
    warning->SetPosition(800, 10);
    m_Components.push_back(warning);
}

//Update is called once per frame. 
void Game::Update(float dt)
{
    //TODO: Format this properly (16 rows, 2 columns, 8 bits per column)
    std::stringstream out;
    std::string kbd = m_Keyboard->GetKeyboardState().to_string();
    std::reverse(kbd.begin(), kbd.end());
    out << "Keyboard State [Starting from bit 0]: \n" << kbd.substr(0, 64) << std::endl << kbd.substr(65, 128) << std::endl << kbd.substr(129, 196) << std::endl;
    keyboardView->SetText(out.str());

    if (m_Keyboard->KeyDown(KB_FNC_F1)) {
        m_FramerateLimit = 0;
    }
    if (m_Keyboard->KeyDown(KB_FNC_F2)) {
        m_FramerateLimit = 15;
    }
    if (m_Keyboard->KeyDown(KB_FNC_F3)) {
        m_FramerateLimit = 30;
    }
    if (m_Keyboard->KeyDown(KB_FNC_F4)) {
        m_FramerateLimit = 60;
    }

}

//FixedUpdate is called at a constant rate.
void Game::FixedUpdate(float dt)
{
}


//Exit is called before the application shuts down.
void Game::Exit()
{
}
