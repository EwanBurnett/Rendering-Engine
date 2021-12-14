#pragma once

#include "../Backend/Graphics.h"
#include "Mesh.h"
#include "ModelMaterial.h"
#include <String>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Engine {

    class Mesh;

    class Model {
    public:
        Model(D3D11_Graphics* gfx, std::string& fileName, bool bFlipUVs = false);
        ~Model();

        D3D11_Graphics* Graphics();

        bool HasMeshes() const;
        bool HasMaterials() const;

        std::vector<Mesh*>& Meshes();
        std::vector<ModelMaterial*>& Materials();

    private:
        std::vector<Mesh*> m_Meshes;
        std::vector<ModelMaterial*> m_Materials;

        D3D11_Graphics* m_Graphics;
    };

}