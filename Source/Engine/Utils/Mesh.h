//#pragma once
//#include <string>
//#include <vector>
//#include <DirectXMath.h>
//#include <Windows.h>
//#include <d3d11.h>
//
//struct aiMesh;
//
//namespace Engine {
//    class Material;
//    class ModelMaterial;
//
//    class Model;
//
//    class Mesh {
//        friend class Model;
//
//    public:
//        Mesh(Model& model, ModelMaterial* material);
//        ~Mesh();
//        
//        Model& GetModel();
//        ModelMaterial& GetMaterial();
//
//        void CreateIndexBuffer(/*Index Buffer** */);
//        //Accessor methods for mesh properties
//        const std::string& Name() const;
//        
//        const std::vector<DirectX::XMFLOAT3>& Vertices() const;
//        const std::vector<DirectX::XMFLOAT3>& Normals() const;
//        const std::vector<DirectX::XMFLOAT3>& Tangents() const;
//        const std::vector<DirectX::XMFLOAT3>& Binormals() const;
//        const std::vector<std::vector<DirectX::XMFLOAT3>*>& TexCoords() const;
//        const std::vector<std::vector<DirectX::XMFLOAT3>*>& VertexColours() const;
//
//        UINT FaceCount() const;
//        const std::vector<UINT>& Indices() const;
//
//    private:
//        Mesh(Model& model, aiMesh& mesh);
//        Mesh(const Mesh& rhs);
//        Mesh& operator = (const Mesh& rhs);
//
//        Model& m_Model;
//        ModelMaterial* m_Material;
//        std::string m_Name;
//
//        std::vector<DirectX::XMFLOAT3>& m_Vertices;
//        std::vector<DirectX::XMFLOAT3>& m_Normals;
//        std::vector<DirectX::XMFLOAT3>& m_Tangents;
//        std::vector<DirectX::XMFLOAT3>& m_Binormals;
//        std::vector<std::vector<DirectX::XMFLOAT3>*>& m_TexCoords;
//        std::vector<std::vector<DirectX::XMFLOAT3>*>& m_VertexColours;
//
//        UINT m_FaceCount;
//        std::vector<UINT> m_Indices;
//    };
//}