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
    keyboardView->SetPosition(500, 500);
    keyboardView->SetText(m_Keyboard->GetKeyboardState().to_string());
}

//Update is called once per frame. 
void Game::Update(float dt)
{
}

//FixedUpdate is called at a constant rate.
void Game::FixedUpdate(float dt)
{
}


//Exit is called before the application shuts down.
void Game::Exit()
{
}
