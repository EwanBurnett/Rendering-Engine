//#pragma once
//#include "ModelComponent.h"
//
//namespace Engine {
//
//    struct PrimitiveVertex {
//        PrimitiveVertex() {
//            position = DirectX::XMFLOAT3(0, 0, 0);
//            color = DirectX::XMFLOAT4(0, 0, 0, 0);
//        }
//        PrimitiveVertex(DirectX::XMFLOAT3 Position, DirectX::XMFLOAT4 Color) : position(Position), color(Color){}
//
//        DirectX::XMFLOAT3 position;
//        float pad = 1.0f;
//        DirectX::XMFLOAT4 color;
//    };
//
//	class Primitive : public ModelComponent {
//	public:
//		Primitive(D3D11_Graphics* gfx, Camera* cam);
//		void CreateBuffers() override;
//	};
//}