#include "ObjectPool.h"

Engine::ObjectPool* Engine::ObjectPool::m_Instance = nullptr;

Engine::ObjectPool::ObjectPool()
{
	assert(m_Instance == nullptr);
	m_Instance = this;

}

Engine::ObjectPool::~ObjectPool()
{
}

void Engine::ObjectPool::Alloc(int size)
{
	//Allocate a fixed number of objects
	m_Objects.reserve(size);
}

void Engine::ObjectPool::Dealloc()
{
	//Clear the allocated objects
	m_Objects.clear();
}

std::unordered_map<Engine::ID, Engine::GameObject*> Engine::ObjectPool::Objects()
{
	return m_Objects;
}

Engine::GameObject& Engine::ObjectPool::Create()
{
	for (auto& pair : m_Objects) {
		if (pair.second->IsActive() == false) {
			pair.second->SetActive(true);
			return(*pair.second);
		}
	}
	/*ID id = new ID();
	m_Objects.insert(std::pair<id, object>);*/
}


