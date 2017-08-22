#ifndef F3D_MeshFactory_H
#define F3D_MeshFactory_H

#include "../_includesF3D.h"

#include "../Layer2/Mesh/F3D_Mesh.h"

class F3D_MeshFactory
{
public:
	F3D_MeshFactory();
	~F3D_MeshFactory();

	F3D_Mesh* loadMesh(const std::string& name, const std::string& path) const;

protected:


};

#endif