//#include "Model.h"
//#include "../Backend/Graphics.h"
//#include "Mesh.h"
////#include "Material.h"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//class Mesh;
//class ModelMaterial;
//
//Engine::Model::Model(D3D11_Graphics* gfx, std::string& fileName, bool bFlipUVs) : 
//    m_Graphics(gfx), m_Meshes(), m_Materials()
//{
//    //Initialize an Asset Importer
//    Assimp::Importer importer;
//
//    UINT flags = 
//        aiProcess_Triangulate |
//        aiProcess_JoinIdenticalVertices |
//        aiProcess_SortByPType |
//        aiProcess_FlipWindingOrder;
//
//    if (bFlipUVs) {
//        flags |= aiProcess_FlipUVs;
//    }
//
//    //Initialize the asset importer scene
//    const aiScene* scene = importer.ReadFile(fileName, flags);
//
//    if (scene == nullptr) {
//        //TODO: Replace with debug layer
//    }
//
//    //Add the materials from the scene
//    if (scene->HasMaterials()) {
//        for (UINT i = 0; i < scene->mNumMaterials; i++) {
//            //m_Materials.push_back(new Material(*this, scene->mMaterials[i]));
//        }
//    }
//
//    //Add the meshes from the scene
//    if (scene->HasMeshes()) {
//        for (UINT i = 0; i < scene->mNumMeshes; i++) {
//            Mesh* mesh = new Mesh(*this, *scene->mMeshes[i]);
//            m_Meshes.push_back(mesh);
//        }
//    }
//}
//
//Engine::Model::~Model()
//{
//    for (auto& mesh : m_Meshes) {
//        delete(mesh);
//    }
//
//    for (auto& mat : m_Materials) {
//        delete(mat);
//    }
//}
//
//bool Engine::Model::HasMeshes() const
//{
//    //Return true if any meshes are found
//    return (m_Meshes.size() > 0);
//}
//
//bool Engine::Model::HasMaterials() const
//{
//    return (m_Materials.size() > 0);
//}
//
////std::vector<Mesh*>& Engine::Model::Meshes() const
////{
////    return m_Meshes;
////}
////
////std::vector<ModelMaterial*>& Engine::Model::Materials() const
////{
////    return m_Materials;
////}
