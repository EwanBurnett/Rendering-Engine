#pragma once
#include <map>
#include <memory>
#include <string>
#include <Windows.h>
#include "..\Components\GameComponent.h"

namespace Engine {
	//TODO: Implement GameObjects, as containers and controllers for Component objects
	//class GameObject {
	//public:
	//	GameObject();
	//	GameObject(unsigned int uid);
	//	virtual ~GameObject();

	//	virtual void Init();
	//	virtual void Update(float dt);
	//	virtual void Draw(float dt);

	//	GameComponent* GetComponent(std::string id);
	//	void SetActive(bool state);
	//	bool IsActive();

	//protected:
	//	std::map<std::string, GameComponent*> m_Components;
	//	bool m_bIsActive;
	//	unsigned int m_UID = -1;
	//};

	//class DebugObject : public GameObject {
	//public:
	//	void Update(float dt) override {
	//		OutputDebugString(L"Hi");
	//	}
	//};

	class GameObject {
		//Helper Type Definitions
	public:
		typedef unsigned long ObjectID;
		typedef std::shared_ptr<GameObject> StrongGameobjectPtr;
		typedef std::map<Engine::GameComponent::ComponentID, Engine::GameComponent> Components;

		explicit GameObject(ObjectID ID);
		~GameObject();

		bool Init();
		virtual void Start();
		virtual void Update(float dt);
		virtual void Draw(float dt);

		//Accessor Methods
		ObjectID ID() const;
		bool IsActive() const;

		void SetActive(bool state);

		template <class ComponentType>
		std::weak_ptr<ComponentType> GetComponent(Engine::GameComponent::ComponentID ID) {
			Components::iterator itr = m_Components.find(ID);
			if (itr != m_Components.end()) {
				std::shared_ptr<GameComponent> pBase(itr->second);
				std::shared_ptr<ComponentType> pSub(std::tr1::static_pointer_cast<ComponentType>(pBase));
				std::weak_ptr<ComponentType> pWeakSub(pSub);

				return pWeakSub;
			}

			else {
				return std::weak_ptr<ComponentType>();
			}
		}

	private:
		ObjectID m_ID;
		bool m_IsActive;

		Components m_Components;

	};
}

