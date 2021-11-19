#pragma once

#include "../Backend/Graphics.h"
#include <String>

namespace Engine {

    class Mesh;
    class ModelMaterial;

    class Model {
    public:
        Model(D3D11_Graphics* gfx, std::string& fileName, bool bFlipUVs = false);
        ~Model();

        D3D11_Graphics* Graphics();

        bool HasMeshes() const;
        bool HasMaterials() const;

        std::vector<Mesh*>& Meshes() const;
        std::vector<ModelMaterial*>& Materials() const;

    private:
        std::vector<Mesh*> m_Meshes;
        std::vector<ModelMaterial*> m_Materials;

        D3D11_Graphics* m_Graphics;


    };

}