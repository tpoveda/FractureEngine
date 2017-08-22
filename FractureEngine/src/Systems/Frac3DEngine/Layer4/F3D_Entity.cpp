#include "../../../../include/Systems/Frac3DEngine/Layer4/F3D_Entity.h"

F3D_Entity::F3D_Entity(std::string initId, F3D_Entity* initParent)
{
	id = initId;
	parent = initParent;

	for (int i = 0; i < KNUM_SYSTEMS; i++)
	{
		requiredSystem[i] = 0;
	}
}

F3D_Entity::~F3D_Entity()
{
	std::cout << "Soy " << id << " y voy a eliminarme." << std::endl;

	// Cada entity elimina sus componentes, dado que los ha creado el , debe eliminarlos y liberarlos
	for (std::map< int, FE_Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		std::cout << "\tElimino el componente " << (*it).second->getType() << " que tenia asociado." << std::endl;
		delete((*it).second);
		(*it).second = NULL;
	}
	components.clear();

	// Cada entity limpia su mapa de entidades, dado que no ha creado el las entidades.Ya se encarga
	// el entity manager de eliminar y liberar todos los que haya pendientes de este entity.
	for (std::map<std::string, F3D_Entity*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		(*it).second = NULL;
	}
	children.clear();

	// Cada entity libera a su padre de él, llamando a su removeChild
	if (parent!= NULL)
		parent->removeChild(id);
	parent = NULL;
}


std::string F3D_Entity::getId()
{
	return id;
}



bool F3D_Entity::addComponent(int componentType)
{
	if (componentType >= KNUM_COMPONENTS)
	{
		std::cout << "El componente " << componentType << " no existe aun en FractureEngine." << std::endl;
		return false;
	}

	if (components.find(componentType) == components.end() )
	{
		components.insert(std::pair<int, FE_Component*>(componentType, newComponentByType(componentType)));
		checkSystems();
		std::cout << "Añadido el componente " << componentType << " a la entidad " << id << "." << std::endl;
		return true;
	}

	std::cout << "La entidad " << id << " ya tiene el componente " << componentType << "." << std::endl;
	return false;
}

FE_Component* F3D_Entity::getComponent(int componentToGet)
{
	std::map<int, FE_Component*>::iterator it = components.find(componentToGet);
	if (it != components.end())
	{
		return (*it).second;
	}
	else
	{
		std::cout << "No existe el componente " << componentToGet << "." << std::endl;
		return NULL;
	}
}

bool F3D_Entity::removeComponent(int componentType)
{
	std::map< int, FE_Component*>::iterator it = components.find(componentType);
	if (it != components.end() ){
		delete((*it).second);
		(*it).second = NULL;
		
		components.erase(it);
		checkSystems();
		std::cout << "Eliminado el componente " << id << " de la entidad " << componentType << "." << std::endl;
		return true;
	}

	std::cout << "La entidad "<< id <<" no tiene el componente " << componentType << "." << std::endl;
	return false;
}



bool F3D_Entity::addChild(F3D_Entity* child)
{
	if (children.find(child->getId()) == children.end())
	{
		children.insert(std::pair<std::string, F3D_Entity*>(child->getId(), child));
		std::cout << "Añadido " << child->getId() << " como hijo de la entidad " << id << "." << std::endl;
		return true;
	}

	std::cout << "La entidad " << id << " ya tiene como hijo a " << child->getId() << "." << std::endl;
	return false;
}

bool F3D_Entity::addChildren(std::vector<F3D_Entity*> childrenVector)
{
	// Variable que indica si ha habido tan solo un error.
	bool allRight = true; 

	for (std::vector<F3D_Entity*>::iterator it = childrenVector.begin(); it != childrenVector.end(); ++it){

		if ( !addChild( *it ) )
			allRight = false;
	}
	return allRight;

}

bool F3D_Entity::removeChild(std::string childToRemove)
{
	std::map<std::string, F3D_Entity*>::iterator it = children.find(childToRemove);
	if (it != children.end()){
		//F3D_Entity* searchedRoot = this;
		std::cout << "Desheredado el hijo " << childToRemove << " de la entidad " << id << "." << std::endl;
		/*while (searchedRoot->parent != NULL)
		{
			searchedRoot = searchedRoot->parent;
		}
		(*it).second->parent = searchedRoot;
		searchedRoot->addChild((*it).second);
		cout << "Ahora " << childToRemove << "tiene como padre a " << searchedRoot->id << "." << endl;*/
		children.erase(it);
		return true;
	}

	std::cout << "La entidad " << id << " no tiene a " << childToRemove << " como hijo." << std::endl;
	return false;
}

std::vector<F3D_Entity*> F3D_Entity::getAll()
{
	std::vector<F3D_Entity*> res;
	std::vector<F3D_Entity*> aux;

	for (std::map<std::string, F3D_Entity*>::iterator it = children.begin(); it != children.end(); it++)
	{
		res.push_back((*it).second);
		aux = (*it).second->getAll();
		for (int i = 0; i < aux.size(); i++)
		{
			res.push_back(aux[i]);
		}
	}

	return res;
}


std::vector<F3D_Entity*> F3D_Entity::getChildren()
{
	std::vector<F3D_Entity*> res;
	
	for (std::map<std::string, F3D_Entity*>::iterator it = children.begin(); it != children.end(); it++)
	{
		res.push_back((*it).second);
	}

	return res;
}

std::vector<F3D_Entity*> F3D_Entity::getBrothers()
{
	return parent->getChildren();
}

std::vector<F3D_Entity*> F3D_Entity::getBrothersWithoutMe()
{
	std::vector<F3D_Entity*> res = parent->getChildren();

	for (int i = 0; i < res.size(); ++i)
	{
		if (res[i]->getId() == id)
		{
			res.erase(res.begin()+i);
			i = res.size();
		}
	}

	return res;

}


void F3D_Entity::setParent(F3D_Entity* newParent)
{
	if (parent != NULL)
		parent->removeChild(id);
	parent = newParent;
}

F3D_Entity* F3D_Entity::getParent()
{
	return parent;
}



FE_Component* F3D_Entity::newComponentByType(int componentType)
{

	FE_Component* aux;
	
		switch (componentType)
		{
			case Transform:
				aux = new FEC_Transform();
				break;

			case Texture:
				aux = new FEC_Texture();
				break;

			case Mesh:
				aux = new FEC_Mesh();
				break;

			case AnimatedMesh:
				aux = new FEC_AnimationMesh();
				break;

			case Heightmap:
				aux = new FEC_AnimationMesh();
				break;
			
			case Camera:
				aux = new FEC_AnimationMesh();
				break;

			case Move:
				aux = new FEC_Move();
				break;

			case Input_Keyboard:
				aux = new FEC_Keyboard();
				break;

			case Input_Mouse:
				aux = new FEC_Mouse();
				break;

			case Input_Joystick:
				aux = new FEC_Joystick();
				break;

			case Image:
				aux = new FEC_Image();
				break;

			case Sprite:
				aux = new FEC_Sprite();
				break;

			case Callback:
				aux = new FEC_Callback();
				break;

			case CollisionShape:
				aux = new FEC_CollisionShapeType();
				break;

			case CollisionBody:
				aux = new FEC_CollisionBodyType();
				break;

			case CollisionObject:
				aux = new FEC_CollisionObjectType();
				break;

			case CollisionWorld:
				aux = new FEC_CollisionWorldType();
				break;

			case IABehavior:
				aux = new FEC_IABehaviorType();
				break;

			case NetReceiver:
				aux = new FEC_NetReceiver();
				break;

			case NetSender:
				aux = new FEC_NetSender();
				break;

			default:
				std::cout << "El componente asignado no existe." << std::endl;
				break;
		}

		return aux;

}

// Por terminar
void F3D_Entity::checkSystems(){

	for (int i = 0; i < KNUM_SYSTEMS; i++)
		requiredSystem[i] = 0;

	// Para el sistema de render
	if (components.find(Mesh) != components.end())
		requiredSystem[Render] = 1;
	
	// Para el sistema de movimiento
	if (components.find(Move) != components.end())
		requiredSystem[Movement] = 1;

	// Para el sistema de input
	if (components.find(Input_Keyboard) != components.end() ||
		components.find(Input_Mouse) != components.end() ||
		components.find(Input_Joystick) != components.end())
		requiredSystem[Input] = 1;

	// Para el sistema de networking
	if (components.find(NetSender) != components.end() ||
		components.find(NetReceiver) != components.end() )
		requiredSystem[Networking] = 1;
}



/* Zona de getComponents por tipo de componente*/

FEC_Transform* F3D_Entity::getComponent_Transform()
{
	return (FEC_Transform*)getComponent(Transform);
}

FEC_Texture* F3D_Entity::getComponent_Texture()
{
	return (FEC_Texture*)getComponent(Texture);
}

FEC_Mesh* F3D_Entity::getComponent_Mesh()
{
	return (FEC_Mesh*)getComponent(Mesh);
}

FEC_Heightmap* F3D_Entity::getComponent_Heightmap()
{
	return (FEC_Heightmap*)getComponent(Heightmap);
}

FEC_Camera* F3D_Entity::getComponent_Camera()
{
	return (FEC_Camera*)getComponent(Camera);
}

FEC_Move* F3D_Entity::getComponent_Move()
{
	return (FEC_Move*)getComponent(Move);
}

FEC_Keyboard* F3D_Entity::getComponent_Keyboard()
{
	return (FEC_Keyboard*)getComponent(Input_Keyboard);
}

FEC_Mouse* F3D_Entity::getComponent_Mouse()
{
	return (FEC_Mouse*)getComponent(Input_Mouse);
}

FEC_Joystick* F3D_Entity::getComponent_Joystick()
{
	return (FEC_Joystick*)getComponent(Input_Joystick);
}

FEC_Image* F3D_Entity::getComponent_Image()
{
	return (FEC_Image*)getComponent(Image);
}

FEC_Sprite* F3D_Entity::getComponent_Sprite()
{
	return (FEC_Sprite*)getComponent(Sprite);
}

FEC_Callback* F3D_Entity::getComponent_Callback()
{
	return (FEC_Callback*)getComponent(Callback);
}

FEC_CollisionShapeType* F3D_Entity::getComponent_CollisionShape()
{
	return (FEC_CollisionShapeType*)getComponent(CollisionShape);
}

FEC_CollisionBodyType* F3D_Entity::getComponent_CollisionBody()
{
	return (FEC_CollisionBodyType*)getComponent(CollisionBody);
}

FEC_CollisionObjectType* F3D_Entity::getComponent_CollisionObject()
{
	return (FEC_CollisionObjectType*)getComponent(CollisionObject);
}

FEC_CollisionWorldType* F3D_Entity::getComponent_CollisionWorld()
{
	return (FEC_CollisionWorldType*)getComponent(CollisionWorld);
}

FEC_IABehaviorType* F3D_Entity::getComponent_IABehavior()
{
	return (FEC_IABehaviorType*)getComponent(IABehavior);
}

FEC_NetReceiver* F3D_Entity::getComponent_NetReceiver()
{
	return (FEC_NetReceiver*)getComponent(NetReceiver);
}

FEC_NetSender* F3D_Entity::getComponent_NetSender()
{
	return (FEC_NetSender*)getComponent(NetSender);
}