#include <iostream>
#include "../../../../include/Systems/Frac3DEngine/Layer5/F3D_MeshFactory.h"

F3D_MeshFactory::F3D_MeshFactory()
{
}

F3D_MeshFactory::~F3D_MeshFactory()
{
}

F3D_Mesh* F3D_MeshFactory::loadMesh(const std::string& name, const std::string& path) const
{
	F3D_Mesh* mesh = new F3D_Mesh(name, path);
	return mesh;
}