#include "ResourceAllocator.h"

ResourceAllocator* ResourceAllocator::m_sInstance = nullptr;
D3D11_Graphics* ResourceAllocator::m_Graphics = nullptr;
std::map<std::string, Engine::Model*> ResourceAllocator::m_ModelResources;
std::map<std::wstring, ID3D11ShaderResourceView*> ResourceAllocator::m_TextureResources;

ResourceAllocator::ResourceAllocator(D3D11_Graphics* gfx)
{
    if (m_sInstance != nullptr) {
        //Something went wrong
    }
    m_sInstance = this;
    m_Graphics = gfx;
}

Engine::Model* ResourceAllocator::GetModel(std::string name)
{
    //Try to load the mesh from the resource map. If that fails, create a new one.
    if (m_ModelResources.find(name) == m_ModelResources.end()) {
        Engine::Model* model = new Engine::Model(m_Graphics, name);
        m_ModelResources.insert(m_ModelResources.end(), std::pair<std::string, Engine::Model*>(name, model));  //Add the model to the map, so we don't need to load it again.
    }

    return m_ModelResources.at(name);

}

ID3D11ShaderResourceView* ResourceAllocator::GetTexture(std::wstring name)
{
    //Try to load the mesh from the resource map. If that fails, create a new one.
    if (m_TextureResources.find(name) == m_TextureResources.end()) {
        ID3D11ShaderResourceView* res;
        //TODO: Switch based on file extention (one for dds, one for other formats.)
    //HRESULT hr = DirectX::CreateWICTextureFromFile(m_pDevice.Get(), m_pContext.Get(), textureName.c_str(), nullptr, &m_TextureView);
        HRESULT hr = DirectX::CreateDDSTextureFromFile(m_Graphics->Device().Get(), m_Graphics->Context().Get(), name.c_str(), nullptr, &res);
        if (FAILED(hr)) {
            //TODO: Do some error handling
            OutputDebugStringA((LPCSTR)name.c_str());
            OutputDebugStringA("Unable to load specified texture. Attempting to use default texture instead.");

            //If the original texture can't be loaded, use the default texture instead
            hr = DirectX::CreateDDSTextureFromFile(m_Graphics->Device().Get(), m_Graphics->Context().Get(), L"D:\\University\\Projects\\Year 2\\Rendering Engine\\Build\\Debug\\Resources\\Textures\\DefaultTexture.dds", nullptr, &res);

            if (FAILED(hr)) {
                OutputDebugStringA("Unable to load default texture.");
                assert(false);
            }
        }


        m_TextureResources.insert(m_TextureResources.end(), std::pair<std::wstring, ID3D11ShaderResourceView*>(name, res));  //Add the model to the map, so we don't need to load it again.
    }

    return m_TextureResources.at(name);
}
