#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_TextureFactory.h"
#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_TextureCubeMapManager.h"

F3D_TextureCubeMapManager::F3D_TextureCubeMapManager() :
F3D_Singleton<F3D_TextureCubeMapManager>(), allTextures()
{
}

F3D_TextureCubeMapManager::~F3D_TextureCubeMapManager()
{
}

void F3D_TextureCubeMapManager::addTexture(const std::string& id, const Frac3DTextureCubeMap& texture)
{
	allTextures[id] = texture;
}

Frac3DTextureCubeMap F3D_TextureCubeMapManager::createTexture(const std::string& id, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	F3D_TextureFactory textureFactory;

	if (!allTextures.contains(posX))
	{
		allTextures[posX] = textureFactory.loadTextureCubeMap(id, posX, negX, posY, negY, posZ, negZ, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		return allTextures[posX];
	}
	return allTextures[posX];
}

Frac3DTextureCubeMap F3D_TextureCubeMapManager::createTexture(const std::string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	F3D_TextureFactory textureFactory;

	if (!allTextures.contains(filename))
	{
		allTextures[filename] = textureFactory.loadTextureCubeMap(filename, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);
		
		return allTextures[filename];
	}
	return allTextures[filename];
}