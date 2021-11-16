#include "GameComponent.h"
#include <Windows.h>

Engine::GameComponent::GameComponent() : m_bEnabled(true)
{
}

Engine::GameComponent::~GameComponent()
{
}

bool Engine::GameComponent::IsEnabled() const
{
    return m_bEnabled;
}

void Engine::GameComponent::SetEnabled(bool state)
{
    m_bEnabled = state;
}

void Engine::GameComponent::Init()
{
    
}

void Engine::GameComponent::Update(float dt)
{
    
}

void Engine::GameComponent::FixedUpdate(float dt)
{
}

void Engine::GameComponent::Draw(float dt)
{
    
}
