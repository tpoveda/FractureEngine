#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_TextureFactory.h"
#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_Texture2DManager.h"

F3D_Texture2DManager::F3D_Texture2DManager() :
F3D_Singleton<F3D_Texture2DManager>(), allTextures()
{
}

F3D_Texture2DManager::~F3D_Texture2DManager()
{
	auto it = allTextures.begin();
	while (it != allTextures.end())
	{
		it->second.reset();
		it++;
	}
	allTextures.clear();
}

void F3D_Texture2DManager::addTexture(const std::string& key, const Frac3DTexture2D& texture)
{
	allTextures[key] = texture;
}

Frac3DTexture2D F3D_Texture2DManager::createTexture(const std::string& filename, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	F3D_TextureFactory textureFactory;

	if (!allTextures.contains(filename))
	{
		allTextures[filename] = textureFactory.loadTexture2D(filename, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);
		return allTextures[filename];
	}
	return allTextures[filename];
}

Frac3DTexture2D F3D_Texture2DManager::createTexture(const std::string& key, int width, int height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	F3D_TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture2D(key, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);
		return allTextures[key];
	}
	return allTextures[key];
}

Frac3DTexture2D F3D_Texture2DManager::createTexture(const std::string& key, GLint internalFormat, int width, int height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	F3D_TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture2D(key, internalFormat, width, height, format, type, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);
		return allTextures[key];
	}
	return allTextures[key];
}

Frac3DTexture2D F3D_Texture2DManager::createTexture(const std::string& key, GLint internalFormat, int width, int height, GLenum format, GLenum type, const unsigned char* pixels, unsigned dataSize, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	F3D_TextureFactory textureFactory;

	if (!allTextures.contains(key))
	{
		allTextures[key] = textureFactory.createTexture2D(key, internalFormat, width, height, format, type, pixels, dataSize, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);
		return allTextures[key];
	}
	return allTextures[key];
}