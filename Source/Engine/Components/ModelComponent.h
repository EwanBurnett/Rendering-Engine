//Ewan Burnett 2021
//Model Component - this component acts as a base for any
//components which require a 3D Model to be represented on screen

#pragma once
#include <DirectXMath.h>

struct Vertex {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal; 
};