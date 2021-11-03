#include "Game.h"
#include "FPSComponent.h"

void Game::Update(float dt)
{
}

void Game::Init()
{
    Engine::FPSComponent* fpsComponent = new Engine::FPSComponent(&m_Time, m_Graphics.get());
    m_Components.push_back(fpsComponent);
}

void Game::Exit()
{
}
