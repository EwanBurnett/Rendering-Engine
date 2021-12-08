#pragma once
#include "ModelComponent.h"

namespace Engine {

	class Primitive : public ModelComponent {
	public:
		Primitive(D3D11_Graphics* gfx, Camera* cam);
		void CreateBuffers() override;
	};
}