#pragma once
#include "GameObject.h"
#include <map>
#include <memory>
#include <assert.h>

namespace Engine {
	typedef std::map<Engine::GameObject::ObjectID, Engine::GameObject::StrongGameobjectPtr*> Pool;

	class ObjectPool {
	public:
		ObjectPool();
		virtual ~ObjectPool();

		void Alloc(int size);
		void Dealloc();

		Pool Objects();

		GameObject& Create();
		Engine::GameObject::StrongGameobjectPtr Create(std::string type);

		void Destroy(GameObject* object);
		void Destroy(std::string id);

	private:
		static ObjectPool* m_Instance;
		Pool m_Objects;
	};
}
