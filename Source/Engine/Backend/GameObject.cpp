#include "GameObject.h"
//
//Engine::GameObject::GameObject()
//{
//}
//
//Engine::GameObject::GameObject(unsigned int uid)
//{
//    m_UID = uid;
//}
//
//Engine::GameObject::~GameObject()
//{
//}
//
//void Engine::GameObject::Init()
//{
//    if (m_bIsActive) {
//        for (auto& component : m_Components) {
//            component.second->Init();
//        }
//    }
//}
//
//void Engine::GameObject::Update(float dt)
//{
//    if (m_bIsActive) {
//        for (auto& component : m_Components) {
//            if (component.second->IsEnabled()) {
//                component.second->Update(dt);
//            }
//        }
//    }
//}
//
//void Engine::GameObject::Draw(float dt)
//{
//    if (m_bIsActive) {
//        for (auto& component : m_Components) {
//            if (component.second->IsEnabled()) {
//                component.second->Draw(dt);
//            }
//        }
//    }
//}
//
//Engine::GameComponent* Engine::GameObject::GetComponent(std::string id)
//{
//    //TODO: null checking
//    return m_Components.find(id)->second;
//}
//
//void Engine::GameObject::SetActive(bool state)
//{
//    m_bIsActive = true;
//}
//
//bool Engine::GameObject::IsActive()
//{
//    return m_bIsActive;
//}

Engine::GameObject::GameObject(ObjectID ID)
{
    m_ID = ID;
    m_IsActive = true;
}

Engine::GameObject::~GameObject()
{
}

bool Engine::GameObject::Init()
{
    return true;
}

void Engine::GameObject::Start()
{
}

void Engine::GameObject::Update(float dt)
{
}

void Engine::GameObject::Draw(float dt)
{
}

Engine::GameObject::ObjectID Engine::GameObject::ID() const
{
    return m_ID;
}

bool Engine::GameObject::IsActive() const
{
    return m_IsActive;
}

void Engine::GameObject::SetActive(bool state)
{
    m_IsActive = state;
}
