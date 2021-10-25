#pragma once
#include <map>
#include <string>
#include <Windows.h>
#include "..\Components\GameComponent.h"

namespace Engine {
	class GameObject {
	public:
		GameObject();
		GameObject(unsigned int uid);
		virtual ~GameObject();

		virtual void Init();
		virtual void Update(float dt);
		virtual void Draw(float dt);

		GameComponent* GetComponent(std::string id);
		void SetActive(bool state);
		bool IsActive();

	protected:
		std::map<std::string, GameComponent*> m_Components;
		bool m_bIsActive;
		unsigned int m_UID = -1;
	};

	class DebugObject : public GameObject {
	public:
		void Update(float dt) override {
			OutputDebugString(L"Hi");
		}
	};
}

