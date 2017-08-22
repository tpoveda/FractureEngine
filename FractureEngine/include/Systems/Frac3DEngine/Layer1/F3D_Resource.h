#ifndef F3D_Resource_H
#define F3D_Resource_H

#include "../Layer0/F3D_ReferenceCounter.h"

#include <string>

//! @class F3D_Resource Clase base para permitir un manejo e inicializacion consistente de los distintos tipos de recursos
//!
//! Cada recurso tendra asocido un GUID unico (la ruta del mismo). Ademas dispone de un contador de referencias y variables
//! miembro para almacenar el nombre del archivo y su ruta.
class F3D_Resource : virtual public F3D_ReferenceCounter
{
public:
	F3D_Resource(const unsigned int GUID, const std::string& name, const std::string& path = "./");
	virtual ~F3D_Resource();
	
	std::string getName();
	std::string getPath();
	std::string getFilename();
	unsigned int getGUID();
	void setGUID(unsigned int GUID);


protected:
	std::string m_name;
	std::string m_path;
	unsigned int m_GUID;
	std::string m_filename;
};

#endif