#include "Mesh.h"
//TODO: #define NOMINMAX before including Windows.h

using namespace DirectX;

Engine::Mesh::Mesh(Model& model, aiMesh& mesh) :
	m_Model(model), m_Material(nullptr), m_Name(mesh.mName.C_Str()), m_Vertices(), m_Normals(), m_Tangents(), m_Binormals(), m_TexCoords(), m_VertexColours(), m_FaceCount(0), m_Indices()
{
	m_Material = m_Model.Materials().at(mesh.mMaterialIndex);

	//Load mesh vertices
	m_Vertices.reserve(mesh.mNumVertices);
	for (size_t i = 0; i < mesh.mNumVertices; i++) {
		m_Vertices.push_back(XMFLOAT3(reinterpret_cast<const float*>(&mesh.mVertices[i])));
	}

	//Load mesh normals
	if (mesh.HasNormals()) {
		m_Normals.reserve(mesh.mNumVertices);
		for (size_t i = 0; i < mesh.mNumVertices; i++) {
			m_Normals.push_back(XMFLOAT3(reinterpret_cast<const float*>(&mesh.mNormals[i])));
		}
	}

	//Load tangents and binormals
	if (mesh.HasTangentsAndBitangents()) {
		m_Tangents.reserve(mesh.mNumVertices);
		for (size_t i = 0; i < mesh.mNumVertices; i++) {
			m_Tangents.push_back(XMFLOAT3(reinterpret_cast<const float*>(&mesh.mTangents[i])));
			m_Binormals.push_back(XMFLOAT3(reinterpret_cast<const float*>(&mesh.mBitangents[i])));
		}
	}

	//Load Texture Coordinates
	UINT uvChannelCount = mesh.GetNumUVChannels();
	for (size_t i = 0; i < uvChannelCount; i++) {
		std::vector<XMFLOAT3>* texCoords = new std::vector<XMFLOAT3>();
		texCoords->reserve(mesh.mNumVertices);
		m_TexCoords.push_back(texCoords);

		aiVector3D* aiTexCoords = mesh.mTextureCoords[i];
		for (size_t j = 0; j < mesh.mNumVertices; j++) {
			texCoords->push_back(XMFLOAT3(reinterpret_cast<const float*>(&aiTexCoords[j])));
		}
	}

	//Load Vertex Colours
	UINT colourChannelCount = mesh.GetNumColorChannels();
	for (size_t i = 0; i < colourChannelCount; i++) {
		std::vector<XMFLOAT3>* vertexColours = new std::vector<XMFLOAT3>();
		vertexColours->reserve(mesh.mNumVertices);
		m_TexCoords.push_back(vertexColours);

		aiColor4D* aiVertexColours = mesh.mColors[i];
		for (size_t j = 0; j < mesh.mNumVertices; j++) {
			vertexColours->push_back(XMFLOAT3(reinterpret_cast<const float*>(&aiVertexColours[j])));
		}
	}

	//Load Faces
	if(mesh.HasFaces()){
		m_FaceCount = mesh.mNumFaces;
		for (size_t i = 0; i < m_FaceCount; i++) {
			aiFace* face = &mesh.mFaces[i];

			for (size_t j = 0; j < face->mNumIndices; j++) {
				m_Indices.push_back(face->mIndices[j]);
			}
		}
	}

}

Engine::Mesh::Mesh(Model& model, ModelMaterial* material) :
	m_Model(model), m_Material(material)
{
}

Engine::Mesh::~Mesh()
{
	//Clean up our references

	for (auto& coord : m_TexCoords) {
		delete(coord);
	}

	for (auto& color : m_VertexColours) {
		delete(color);
	}
}

Engine::Model& Engine::Mesh::GetModel()
{
	return(m_Model);
}

Engine::ModelMaterial& Engine::Mesh::GetMaterial()
{
	return(*m_Material);
}

void Engine::Mesh::CreateIndexBuffer(ID3D11Buffer** ppIndexBuffer)
{
	if (ppIndexBuffer == nullptr) {
		//TODO: Link to debug layer
	}

	D3D11_BUFFER_DESC ibd = { };

	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = static_cast<UINT>(sizeof(UINT) * m_Indices.size());
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	//Initializse the index buffer with our data
	D3D11_SUBRESOURCE_DATA iInitData = { };
	iInitData.pSysMem = &m_Indices[0];

	
	//Attempt to create the index buffer
	if (FAILED(m_Model.Graphics()->Device()->CreateBuffer(&ibd, &iInitData, ppIndexBuffer))) {
		//TODO: Link to Debug Layer
	}

}

const std::vector<DirectX::XMFLOAT3>& Engine::Mesh::Vertices() const
{
	return(m_Vertices);
}

const std::vector<std::vector<DirectX::XMFLOAT3>*>& Engine::Mesh::TexCoords() const
{
	return(m_TexCoords);
}

const std::vector<std::vector<DirectX::XMFLOAT4>*>& Engine::Mesh::VertexColours() const
{
	return(m_VertexColours);
}

const std::vector<UINT>& Engine::Mesh::Indices() const
{
	return(m_Indices);
}
