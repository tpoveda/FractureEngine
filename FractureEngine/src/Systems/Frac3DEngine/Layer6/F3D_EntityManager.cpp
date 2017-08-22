#include "../../../../include/Systems/Frac3DEngine/Layer6/F3D_EntityManager.h"

F3D_EntityManager* F3D_EntityManager::entityManagerPointer = nullptr;

F3D_EntityManager::F3D_EntityManager()
{
	root = new F3D_Entity("root", NULL);
	entities.insert(std::pair<std::string, F3D_Entity*>(root->getId(), root));
	std::cout << "Se ha creado la entidad root." << std::endl;
	std::cout << "Hay  " << entities.size() << " entidades en el mapa." << std::endl;
}

F3D_EntityManager::~F3D_EntityManager()
{
	this->removeEntity("root");
	std::cout << "Hay  " << entities.size() << " entidades en el mapa." << std::endl;
	entities.clear();

}

F3D_Entity* F3D_EntityManager::getEntityById(std::string entityId)
{
	std::map<std::string, F3D_Entity*>::iterator it = entities.find(entityId);
	if ( it != entities.end())
	{
		return (*it).second;
	}	
	else
	{
		std::cout << "No existe la entidad "<< entityId <<"." << std::endl;
		return NULL;
	}
}

F3D_Entity* F3D_EntityManager::createEntity(std::string entityId)
{
	
	if (entities.find(entityId) == entities.end())
	{
		F3D_Entity* aux = new F3D_Entity(entityId, root);
		entities.insert(std::pair<std::string, F3D_Entity*>(entityId, aux));
		root->addChild(aux);
		std::cout << "Se ha creado la entidad " << entityId << "." << std::endl;
		std::cout << "Hay  " << entities.size() << " entidades en el mapa.\n" << std::endl;
		return (*entities.find(entityId)).second ;
	}
	else
	{
		std::cout << "Ya existe la entidad " << entityId << "." << std::endl;
		return NULL;
	}
}

F3D_Entity* F3D_EntityManager::createEntity(std::string entityId, std::string parentId)
{
	std::map<std::string, F3D_Entity*>::iterator it = entities.find(parentId);
	if (it != entities.end())
	{
		return createEntity(entityId, (*it).second);
	}
	else
	{
		std::cout << "No existe la entidad padre " << entityId << "." << std::endl; 
		return NULL;
	}
}

F3D_Entity* F3D_EntityManager::createEntity(std::string entityId, F3D_Entity* initParent)
{
	if ( entities.find(entityId) == entities.end())
	{
		if (entities.find(initParent->getId()) != entities.end())
		{
			F3D_Entity* aux = new F3D_Entity(entityId, initParent);
			entities.insert(std::pair<std::string, F3D_Entity*>(entityId, aux));
			initParent->addChild(aux);
			std::cout << "Se ha creado la entidad " << entityId << "." << std::endl;
			std::cout << "Hay  " << entities.size() << " entidades en el mapa.\n" << std::endl;
			return (*entities.find(entityId)).second;
		}
		else
		{
			std::cout << "No existe la entidad padre " << initParent->getId() << "." << std::endl;
			return NULL;
		}
	}
	else
	{
		std::cout << "Ya existe la entidad " << entityId << "." << std::endl;
		return NULL;
	}
}

bool F3D_EntityManager::removeEntity(std::string entityId)
{
	std::map<std::string, F3D_Entity*>::iterator it = entities.find(entityId);
	if (it != entities.end())
	{
		std::vector<F3D_Entity*> deleteChildren = (*it).second->getChildren();

		for (int i = 0; i < deleteChildren.size(); i++){
			removeEntity(deleteChildren[i]->getId()) ;
		}

		delete((*it).second);
		(*it).second = NULL;

		entities.erase(it);

		std::cout << "Se ha eliminado la entidad " << entityId << "." << std::endl;
		std::cout << "Quedan  " << entities.size() << " entidades aun en el mapa.\n" << std::endl;
		return true;
	}
	else
	{
		std::cout << "No existe la entidad " << entityId << "." << std::endl;
		return false;
	}
}

bool F3D_EntityManager::removeEntity(F3D_Entity* entityToRemove)
{
	return removeEntity(entityToRemove->getId());
}


std::vector<F3D_Entity*>  F3D_EntityManager::getEntitysFor(int system)
{
	std::vector<F3D_Entity*> res;
	
	for (std::map<std::string, F3D_Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		if ((*it).second->requiredSystem[system])
			res.push_back( (*it).second );
	}
	return res;
}