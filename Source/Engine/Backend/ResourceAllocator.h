#pragma once
//Resource Allocator - Ewan Burnett 2021
//A simple resource loader, which maps application resources before they're used.

#include "Graphics.h"
#include <string>
#include <map>
#include <Windows.h>
#include <d3d11.h>
#include "../Utils/Mesh.h"
#include "../Utils/ModelMaterial.h"
#include "../Utils/Model.h"
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

class Mesh;

class ResourceAllocator {
public:
    ResourceAllocator(D3D11_Graphics* gfx);
    static Engine::Model* GetModel(std::string name);
    ID3D11ShaderResourceView* GetTexture(std::wstring name);

private:
    static std::map<std::string, Engine::Model*> m_ModelResources;
    static std::map<std::wstring, ID3D11ShaderResourceView*> m_TextureResources;
    static D3D11_Graphics* m_Graphics;

    static ResourceAllocator* m_sInstance;
};

