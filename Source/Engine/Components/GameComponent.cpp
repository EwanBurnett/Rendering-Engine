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
    OutputDebugString(L"Init Called");
}

void Engine::GameComponent::Update(float dt)
{
    OutputDebugString(L"Update Called");
}

void Engine::GameComponent::Draw(float dt)
{
    OutputDebugString(L"Draw Called");
}
