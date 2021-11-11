#include "Game.h"
#include <Components/FPSComponent.h>
#include <Components/TextComponent.h>
#include <Components/SpriteComponent.h>
#include <iostream>

Engine::TextComponent* textComponent;
Engine::TextComponent* keyboardView;
Engine::FPSComponent* fpsComponent;
Engine::TextComponent* cameraMatrices;
Engine::TextComponent* warning;
Engine::SpriteComponent* sprite;

DirectX::XMFLOAT4X4 viewproj;
int frameLimitSwitch = 0;

//Init is called when the application is started.
void Game::Init()
{
    sprite = new Engine::SpriteComponent(m_Graphics.get());
    sprite->SetPosition(1000, 400);
    m_Components.push_back(sprite);

    textComponent = new Engine::TextComponent(m_Graphics.get());
    textComponent->SetPosition(10, 10);
    textComponent->SetText("Default Rendering Demo\nEwan Burnett [2021]\nA simple demo, demonstrating rendered text.\nFramerate Controls:\n    F1 - uncapped\n    F2 - 15 FPS\n    F3 - 30 FPS\n    F4 - 60 FPS");
    m_Components.push_back(textComponent);

    fpsComponent = new Engine::FPSComponent(&m_Time, m_Graphics.get());
    fpsComponent->TextPosition() = DirectX::XMFLOAT2(400, 10);
    fpsComponent->SetColor(0.0f, 1.0f, 0.25f);
    m_Components.push_back(fpsComponent);

    keyboardView = new Engine::TextComponent(m_Graphics.get());
    keyboardView->SetPosition(10, 460);
    keyboardView->SetColor(0.05f, 0.2f, 1.0f, 1.0f);
    m_Components.push_back(keyboardView);

    warning = new Engine::TextComponent(m_Graphics.get());
    warning->SetText("DON'T EVEN THINK ABOUT MOVING ONTO\nRENDERING BEFORE YOU FULLY IMPLEMENT AND TEST\nALL THIS BACKEND STUFF!!!\n+ Keyboard Input\n- Mouse Input\n- Building Fonts\n- Object Pooling\n+ Camera Matrices\n+ Framerate Limiting\n- Game Objects\n- Byte Alignment\n- OPTIMISATIONS\n+ Warnings\n+ Memory Leaks\n- COM Pointers\n- Sprite Component\n- COMMENTING\n- ARCHITECTURAL DESIGN DOCUMENT!!!!!!!!!\n+ Icons\n- ...and tidying up :D\nHave Fun <3");
    warning->SetColor(1.0f, 0.0f, 0.05f, 1.0f);
    warning->SetPosition(800, 10);
    m_Components.push_back(warning);

    cameraMatrices = new Engine::TextComponent(m_Graphics.get());
    cameraMatrices->SetColor(0.3f, 0.3f, 0.5f, 1.0f);
    cameraMatrices->SetPosition(700, 500);
    m_Components.push_back(cameraMatrices);

    
}

//Update is called once per frame. 
void Game::Update(float dt)
{
    //TODO: Format this properly (16 rows, 2 columns, 8 bits per column)
    std::stringstream out;
    std::string kbd = m_Keyboard->GetKeyboardState().to_string();

    std::reverse(kbd.begin(), kbd.end());
    kbd.insert(32, "\n");
    kbd.insert(64, "\n");
    kbd.insert(96, "\n");
    kbd.insert(128, "\n");

    std::string kbd2 = m_Keyboard->GetKeyboardState().to_string();

    std::reverse(kbd2.begin(), kbd2.end());
    kbd2.insert(32, "\n");
    kbd2.insert(64, "\n");
    kbd2.insert(96, "\n");
    kbd2.insert(128, "\n");

    //out << "Keyboard State [Starting from bit 0]: \n" << kbd.substr(0, 64) << std::endl << kbd.substr(65, 128) << std::endl << kbd.substr(129, 196) << std::endl;
    out << "Keyboard State [Starting from bit 0]: \n" << kbd << "\n\n Last Keyboard State\n" << kbd2 << std::endl;
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

    if (m_Keyboard->KeyDown(KB_DIR_UP)) {
        m_Camera->Position().x += 0.05f;
    }
    
    DirectX::XMStoreFloat4x4(&viewproj, m_Camera->GetViewProjMatrix());
    DirectX::XMMATRIX m = m_Camera->GetViewProjMatrix();
    std::stringstream out2;
    for (int i = 0; i < 4; i++) {
        XMFLOAT4 r;
        DirectX::XMStoreFloat4(&r, m.r[i]);

        out2 << "[" << r.x << ", " << r.y << ", " << r.z << ", " << r.w << "]" << std::endl;
    }

    cameraMatrices->SetText(out2.str());
}

//FixedUpdate is called at a constant rate.
void Game::FixedUpdate(float dt)
{
}


//Exit is called before the application shuts down.
void Game::Exit()
{
    delete(textComponent);
    delete(fpsComponent);
    delete(keyboardView);
    delete(warning);
}
