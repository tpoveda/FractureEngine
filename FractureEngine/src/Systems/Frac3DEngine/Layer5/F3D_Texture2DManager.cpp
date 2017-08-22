#include "../../../../include/Systems/Frac3DEngine/Layer5/F3D_Texture2DManager.h"
#include "../../../../include/Systems/Frac3DEngine/Layer5/F3D_TextureFactory.h"

F3D_Texture2DManager::F3D_Texture2DManager()
{
	texture2DManager = new F3D_ResourceManagerBase<F3D_Texture2D>();
}

F3D_Texture2DManager::~F3D_Texture2DManager()
{
	delete texture2DManager;
}

unsigned int F3D_Texture2DManager::createTexture(const std::string& name, const std::string& path, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic)
{
	F3D_Texture2D* temp = texture2DManager->GetElement(name, path);
	if (temp != NULL)
	{
		return texture2DManager->Add(temp);
	}

	F3D_TextureFactory textureFactory;
	return texture2DManager->Add(textureFactory.loadTexture2D(name, path, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

F3D_Texture2D* F3D_Texture2DManager::getTexture(unsigned GUID)
{
	return texture2DManager->GetElement(GUID);
}

void F3D_Texture2DManager::removeTexture(unsigned int GUID)
{
	texture2DManager->Remove(GUID);
}