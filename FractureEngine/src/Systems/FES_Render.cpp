
#include "../../include/Systems/FES_Render.h"
#include "../../include/Systems/Frac3DEngine/Layer6/F3D_RenderManager.h"


FES_Render::FES_Render() :
EntityManagerPointer(nullptr),
RenderManagerPointer(nullptr),
ResourceManagerPointer(nullptr)
{
	id = Render;
	enabled = true;
}

FES_Render::~FES_Render()
{
	EntityManagerPointer->terminate();
	RenderManagerPointer->terminate();
	ResourceManagerPointer->terminate();
	EntityManagerPointer = nullptr;
	RenderManagerPointer = nullptr;
	ResourceManagerPointer = nullptr;
}

void FES_Render::init()
{
	// almacenamos punteros a las distintas instancias de los subsistemas del motor de render
	// NOTA: Al llamar al constructor de los distintos subsistemas, estos se inicializan de forma automatica
	EntityManagerPointer = F3D_EntityManager::getInstance();
	RenderManagerPointer = F3D_RenderManager::getInstance();
	ResourceManagerPointer = F3D_ResourceManager::getInstance();
}

void FES_Render::processEntities(std::vector<F3D_Entity*> entities)
{
	for (std::vector<F3D_Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		// actualizamos la transformacion de los objetos
		(*it)->getComponent_Transform()->update();
		if ((*it)->getParent() != nullptr)
		{
			(*it)->getComponent_Transform()->setMatrix((*it)->getParent()->getComponent_Transform()->getMatrix() * (*it)->getComponent_Transform()->getMatrix());
		}
	}
}

F3D_EntityManager* FES_Render::getEntityManager()
{
	return EntityManagerPointer;
}

F3D_RenderManager* FES_Render::getRenderManager()
{
	return RenderManagerPointer;
}

F3D_ResourceManager* FES_Render::getResourceManager()
{
	return ResourceManagerPointer;
}