#include "Game.h"
#include <Components/FPSComponent.h>
#include <Components/TextComponent.h>

Engine::TextComponent* textComponent;
Engine::TextComponent* keyboardView;

//Init is called when the application is started.
void Game::Init()
{
    textComponent = new Engine::TextComponent(m_Graphics.get());
    textComponent->SetPosition(10, 10);
    textComponent->SetText("Default Rendering Demo\nEwan Burnett [2021]\nA simple demo, demonstrating rendered text.");
    m_Components.push_back(textComponent);

    Engine::FPSComponent* fpsComponent = new Engine::FPSComponent(&m_Time, m_Graphics.get());
    fpsComponent->TextPosition() = DirectX::XMFLOAT2(10, 100);
    fpsComponent->SetColor(0, 1, 0.25);
    m_Components.push_back(fpsComponent);

    keyboardView = new Engine::TextComponent(m_Graphics.get());
    keyboardView->SetPosition(0, 660);
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
    out << "Keyboard State: " << kbd.substr(0, 32) << std::endl << kbd.substr(32, 64) << std::endl << kbd.substr(64, 96) << std::endl << kbd.substr(96, 128) << std::endl << kbd.substr(128, 160) << std::endl;
    keyboardView->SetText(out.str());
}

//FixedUpdate is called at a constant rate.
void Game::FixedUpdate(float dt)
{
}


//Exit is called before the application shuts down.
void Game::Exit()
{
}
