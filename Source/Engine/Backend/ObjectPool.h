#pragma once
#include "GameObject.h"
#include <unordered_map>
#include <memory>
#include <assert.h>

namespace Engine {
	//TODO: Implement this
	typedef unsigned int ID;

	class ObjectPool {
	public:
		ObjectPool();
		virtual ~ObjectPool();

		void Alloc(int size);
		void Dealloc();

		std::unordered_map<Engine::ID, Engine::GameObject*> Objects();

		GameObject& Create();
		void Create(ID id);

		void Destroy(GameObject* object);
		void Destroy(ID id);

	private:
		static ObjectPool* m_Instance;
		std::unordered_map<Engine::ID, Engine::GameObject*> m_Objects;
	};
}
