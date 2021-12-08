#include "ModelMaterial.h"

//Assert the static instance
std::map<Engine::TextureType, UINT> Engine::ModelMaterial::m_TextureTypeMappings;

Engine::ModelMaterial::ModelMaterial(Model& model) :
	m_Model(model), m_Textures()
{
	InitTextureTypeMappings();
}

Engine::ModelMaterial::~ModelMaterial()
{
}

void Engine::ModelMaterial::InitTextureTypeMappings()
{
	if (m_TextureTypeMappings.size() != TextureType::End) {
		m_TextureTypeMappings[TextureType::Diffuse] = aiTextureType_DIFFUSE;
		m_TextureTypeMappings[TextureType::SpecularMap] = aiTextureType_SPECULAR;
		m_TextureTypeMappings[TextureType::Ambient] = aiTextureType_AMBIENT;
		m_TextureTypeMappings[TextureType::Heightmap] = aiTextureType_HEIGHT;
		m_TextureTypeMappings[TextureType::Normalmap] = aiTextureType_NORMALS;
		m_TextureTypeMappings[TextureType::SpecularPowerMap] = aiTextureType_SHININESS;
		m_TextureTypeMappings[TextureType::DisplacementMap] = aiTextureType_DISPLACEMENT;
		m_TextureTypeMappings[TextureType::LightMap] = aiTextureType_LIGHTMAP;

	}
}

Engine::ModelMaterial::ModelMaterial(Model& model, aiMaterial* material) :
	m_Model(model), m_Textures()
{
	InitTextureTypeMappings();

	aiString name;
	material->Get(AI_MATKEY_NAME, name);
	m_Name = name.C_Str();

	//Retrieve the mapped texture type
	for (TextureType type = (TextureType)0; type < TextureType::End; type = (TextureType)(type + 1)) {
		aiTextureType mappedTextureType = (aiTextureType)m_TextureTypeMappings[type];

		UINT textureCount = material->GetTextureCount(mappedTextureType);

		if (textureCount > 0) {
			std::vector<std::wstring>* textures = new std::vector<std::wstring>();
			m_Textures.insert(std::pair<TextureType, std::vector<std::wstring>*>(type, textures));

			textures->reserve(textureCount);

			for (size_t texIndex = 0; texIndex < textureCount; texIndex++) {
				aiString path;
				
				if (material->GetTexture(mappedTextureType, texIndex, &path) == AI_SUCCESS) {
					std::string sPath = path.C_Str();
					//TODO: Write wstring -> string conversion code
					//std::wstring wPath = (std::wstring)sPath;
					//textures->push_back(wPath);
				}
			}
		}
	}
}