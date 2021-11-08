#include "Game.h"
#include <Components/FPSComponent.h>

//Init is called when the application is started.
void Game::Init()
{
    Engine::FPSComponent* fpsComponent = new Engine::FPSComponent(&m_Time, m_Graphics.get());
    m_Components.push_back(fpsComponent);
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
