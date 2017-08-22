#include "../../../../include/Systems/Frac3DEngine/Layer6/F3D_ResourceManager.h"

F3D_ResourceManager::F3D_ResourceManager() :
F3D_Singleton<F3D_ResourceManager>(),
texture2DManager(nullptr)
{
	// inicializamos los distintos gestores de recursos
	texture2DManager = new F3D_Texture2DManager();
	meshManager = new F3D_MeshManager();
}

F3D_ResourceManager::~F3D_ResourceManager()
{
	delete texture2DManager;
	texture2DManager = nullptr;

	delete meshManager;
	meshManager = nullptr;
}

F3D_Texture2DManager* F3D_ResourceManager::getTextureManager()
{
	return texture2DManager;
}

F3D_MeshManager* F3D_ResourceManager::getMeshManager()
{
	return meshManager;
}