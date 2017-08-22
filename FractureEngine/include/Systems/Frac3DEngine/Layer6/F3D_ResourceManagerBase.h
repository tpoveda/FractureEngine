#ifndef F3D_ResourceManagerBase_H
#define F3D_ResourceManagerBase_H

/******************************************************************************************************************************************************************
*********************** FUNCIONAMIENTO DE LOS RECURSOS Y TIPOS
Para cada tipo de recurso, se deriva una clase desde la clase basica del recurso. Por ejemplo, el recurso Texture2D se derivara de la clase base Resource. La clase 
Texture2D contendra las variables y metodos miembro necesarios para ese tipo de recurso especifico (anchura, altura, etc). El constructor de la clase Texture2D,
recibira los parametros de nombre y ruta. La clase base Resource contendra metodos y miembros generales a todo tipo de los recursos y mantendra un contador de 
referencias para cada recurso. Cada recurso, ademas, dispone de un GUID unico el cual esta asociado a la ruta del recurso. De esta forma, un recurso que se encuentre
en la ruta ./res/textures/ y cuyo nombre sea floorTexture solo podra ser cargado una unica vez aunque una vez cargado puede ser usado por tantas entidades como sea
necesaria. Para controlar la liberacion correcta del recurso usamos los contadores de referencia, cuando este llegue a 0, el recurso se eliminara mientras no sea igual
a 0 significa que alguna entidad necesita este recurso y, por tanto, no deberemos eliminarlo.

*********************** CREACION DEL GESTOR DE RECURSOS
Por cada tipo de recuro creamos una instancia del ResourceManager, asi, cuando creamos un ResourceManager especificamos el tipo de recurso que gestionara y una funcion
callback opcinal que se llamara acuando añadamos un recurso al gestor de recursos. Ademas, el constructor del gestor de recursos inicializa una lista a un vector 
que almacena punteros a los distintos recursos

*********************** ELIMINACION DEL GESTOR DE RECURSOS
El destructor de la clase ResourceManager destruye todos los recursos cargados por esa instancia del ResourceManager y destruye el vector con los punteros a dichos
recursos

*********************** ACCESO
El metodo getResource sirve para acceder a los recursos cargados por el ResourceManager, tiene una unica sobrecarga:
1. Una toma la localizacion del archivo e itera a traves de todos los recursos hasta encontrar un recurso con la misma ruta, si se encuentra ya el recurso cargada
se devuelve ese. Este acceso se ejecuta en un tiempo lineal.

NOTA: Podreiamos mejorar el acceso a los recursos utilizando un GUID como entero, esto mejoraria el acceso a los recursos a O(1) pero por el momento no los usamos
porque creemos que la ruta, aunque el acceso sea algo mas lento, nos parece un GUID mas legible a la hora de trabajar con numerosos recursos. De todas formas, en 
futuras versiones quizas cambiemos esto

Si el recurso no se encuentra a la hora de buscarlo se devuelve NULL. Podemos acceder a los recursos tambien usando el operador [] para facilitar el acceso a los 
recursos (ya no tenemos que llamar al metodo getResource todo el rato).

*********************** ELIMINACION
El borrado de recursos se realiza usando el metodo Remove(). Toma como parametro el GUID y comprueba si la eliminacion es posible. Si es asi, accede al recurso
indexado por el GUID, el contador de referencias se decrementa y si llega a 0 entonces es eliminado. Sin embargo, en la eliminacion almacenamos el 




/******************************************************************************************************************************************************************/
#include <vector>
#include <stack>

#define SAFE_DELETE( p )       { if( p ) { delete ( p );     ( p ) = NULL; } }

//! @class F3D_ResourceManager Clase que menajea diferentes tipos de recursos
//!
//! Usamos una instancia del ResourceManager distinta por cada tipo de recursos, por esta razon, la clase
//! Resource Manager es una clase generica (template)
template<class T>
class F3D_ResourceManagerBase
{
private:
	std::stack<unsigned int> m_handles;
	std::vector<T*> *m_list;	//List of pointers to resources
	void(*CreateResource)(T **resource, const unsigned int handle, const std::string& name, const std::string& path); // Application specific resource creation.

public:
	//-------------------------------------------------------------------------
	// The resource manager class constructor.
	//-------------------------------------------------------------------------
	F3D_ResourceManagerBase()
	{
		m_list = new std::vector<T*>;

	}

	//-------------------------------------------------------------------------
	// The resource manager class destructor.
	//-------------------------------------------------------------------------
	~F3D_ResourceManagerBase()
	{
		EmptyList();
		delete m_list;
	}

	//-------------------------------------------------------------------------
	// Returns a pointer to the vector of resources.
	//-------------------------------------------------------------------------
	std::vector<T*> *GetList()
	{
		return m_list;
	}

	//-------------------------------------------------------------------------
	// Returns a resource by its filename.
	//-------------------------------------------------------------------------
	T* GetElement(const std::string& name, const std::string& path = "./")
	{
		// Ensure the name and path are valid, and the list is valid and not empty.
		if (name.empty() || path.empty() || m_list == NULL || m_list->empty())
			return NULL;

		//// Iterate the list looking for the specified resource.
		for (std::vector<T*>::iterator i = m_list->begin();
			i != m_list->end(); i++)
		{
			if ((*i) != NULL)
			if ((*i)->getName() == name)
			if ((*i)->getPath() == path)
				return (*i);
		}

		// Return NULL if the resource was not found.
		return NULL;
	}

	//-------------------------------------------------------------------------
	// Returns a resource by its handle.
	//-------------------------------------------------------------------------
	T *GetElement(const int handle)
	{
		if (handle < m_list->size() && handle >= 0)
		{
			return (*m_list)[handle];
		}

		return NULL;
	}

	//-------------------------------------------------------------------------
	// Clears the resource list.
	//-------------------------------------------------------------------------
	void EmptyList()
	{
		for (std::vector<T*>::iterator i = m_list->begin();
			i != m_list->end(); i++)
			SAFE_DELETE(*i);

		while (!m_handles.empty())
			m_handles.pop();

		//use vector swapping trick to release previously used memory.
		m_list->clear();
		m_list->swap(*m_list);
	}

	//-------------------------------------------------------------------------
	// Removes the given resource from the manager.
	//-------------------------------------------------------------------------
	void Remove(const unsigned int handle)
	{
		// Ensure the resource to be removed and the list is valid.
		if (handle < 0 || m_list == NULL || handle >= m_list->size() || (*m_list)[handle] == NULL)
			return;

		T * resource = (*m_list)[handle];

		int tempRef = resource->getReferenceCount() - 1;
		if (tempRef == 0)
		{
			// añadimos el GUID al stack de GUIDs libres
			m_handles.push(handle);
			(*m_list)[handle] = NULL;
		}

		// Decrement the resource's reference count.
		resource->Drop();
	}

	unsigned int Add(T* resource)
	{
		if (resource == NULL || m_list == NULL || resource->getName().empty() || resource->getPath().empty())
		{
			return -1;
		}

		if (GetElement(resource->getName(), resource->getPath()) != NULL)
		{
			T* res = GetElement(resource->getName(), resource->getPath());
			res->Grab();
			return res->getGUID();
		}

		// comprobamos si hay algun GUID disponible. Si no es asi, creamos un nuevo GUID
		bool GUIDavailable = !m_handles.empty();
		unsigned int GUID;

		if (GUIDavailable)
		{
			GUID = m_handles.top();
			m_handles.pop();
			resource->setGUID(GUID);
		}
		else
		{
			GUID = m_list->size();
			resource->setGUID(GUID);
		}

		// añadimos el nuevo recurso al maanger. Si hay un GUID disponible, entonces almacenamos
		// el recurso usando ese GUID. Si no, lo añadimos al vector
		if (GUIDavailable) (*m_list)[GUID] = resource;
		else m_list->push_back(resource);

		resource->Grab();

		// devolvemos el GUID
		return GUID;
	}

	unsigned int Add(const std::string& name, const std::string& path)
	{
		if (name.empty() || path.empty())
		{
			return -1;
		}

		T* res = GetElement(name, path);
		res->Grab();
		return res->getGUID();
	}

	//-------------------------------------------------------------------------
	// Overloaded [] operator for easier access
	//-------------------------------------------------------------------------
	T* operator [](unsigned int handle)
	{
		if (handle < m_list->size() && handle >= 0)
			return (*m_list)[handle];

		return NULL;
	}
};

#endif