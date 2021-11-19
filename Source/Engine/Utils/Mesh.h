#pragma once

struct aiMesh;

namespace Engine {
    class Material;
    class ModelMaterial;

    class Model;

    class Mesh {
        friend class Model;

    public:
        Mesh(Model& model, ModelMaterial* material);
        ~Mesh();


    };
}