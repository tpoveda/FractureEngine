#include "../../../../include/Systems/Frac3DEngine/Layer5/F3D_MeshManager.h"
#include "../../../../include/Systems/Frac3DEngine/Layer5/F3D_MeshFactory.h"

F3D_MeshManager::F3D_MeshManager()
{
	meshManager = new F3D_ResourceManagerBase<F3D_Mesh>();
}

F3D_MeshManager::~F3D_MeshManager()
{
	delete meshManager;
}

unsigned int F3D_MeshManager::createMesh(const std::string& name, const std::string& path)
{
	F3D_Mesh* temp = meshManager->GetElement(name, path);
	if (temp != NULL)
	{
		return meshManager->Add(temp);
	}

	F3D_MeshFactory meshFactory;
	return meshManager->Add(meshFactory.loadMesh(name, path));
}

F3D_Mesh* F3D_MeshManager::getMesh(unsigned GUID)
{
	return meshManager->GetElement(GUID);
}

void F3D_MeshManager::removeMesh(unsigned GUID)
{
	meshManager->Remove(GUID);
}