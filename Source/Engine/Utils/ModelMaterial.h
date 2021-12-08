#pragma once
//#define NOMINMAX
#include <string>
#include <map>
#include "Model.h"
#include <assimp/scene.h>

struct aiMaterial;

namespace Engine {
	
	enum TextureType {
		Diffuse = 0,
		SpecularMap,
		Ambient,
		Emissive,
		Heightmap,
		Normalmap,
		SpecularPowerMap,
		DisplacementMap,
		LightMap,
		End
	};

	class ModelMaterial {
		friend class Model;

	public:
		ModelMaterial(Model& model);
		~ModelMaterial();

		Model& GetModel();
		const std::string& Name() const;
		const std::map<TextureType, std::vector<std::wstring>*> Textures() const;

	private:
		static void InitTextureTypeMappings();
		static std::map<TextureType, UINT> m_TextureTypeMappings;

		ModelMaterial(Model& model, aiMaterial* material);
		ModelMaterial(const ModelMaterial& src);

		Model& m_Model;
		std::string m_Name;
		std::map<TextureType, std::vector<std::wstring>*> m_Textures;
	};
}