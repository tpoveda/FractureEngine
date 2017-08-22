#include "../../../../include/Systems/Frac3DEngine/Layer1/F3D_Resource.h"

F3D_Resource::F3D_Resource(const unsigned int GUID, const std::string& name, const std::string& path)
{
	// almacenamos el nombre del recurso
	if (!name.empty()) m_name = name;

	// almacenamos la ruta
	if (!path.empty()) m_path = path;

	// almacenamos el nombre del archivo
	if (!name.empty() && !m_path.empty())
	{
		m_filename = path + name;
	}

	// almacenamos el GUID
	m_GUID = GUID;
}

F3D_Resource::~F3D_Resource()
{
}

std::string F3D_Resource::getName()
{
	return m_name;
}

std::string F3D_Resource::getPath()
{
	return m_path;
}

std::string F3D_Resource::getFilename()
{
	return m_filename;
}

unsigned int F3D_Resource::getGUID()
{
	return m_GUID;
}

void F3D_Resource::setGUID(unsigned int GUID)
{
	m_GUID = GUID;
}