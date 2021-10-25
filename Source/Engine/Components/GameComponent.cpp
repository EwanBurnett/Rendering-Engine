#include "GameComponent.h"

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

void Engine::GameComponent::Draw(float dt)
{
}
