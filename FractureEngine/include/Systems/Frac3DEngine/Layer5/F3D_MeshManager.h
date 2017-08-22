#ifndef F3D_MeshManager_H
#define F3D_MeshManager_H

#include "../_includesF3D.h"

#include "../Layer2/Mesh/F3D_Mesh.h"
#include "../Layer6/F3D_ResourceManagerBase.h"

class F3D_MeshManager
{
public:
	F3D_MeshManager();
	virtual ~F3D_MeshManager();

	unsigned int createMesh(const std::string& name, const std::string& path);
	F3D_Mesh* getMesh(unsigned int GUID);
	void removeMesh(unsigned int GUID);

private:
	F3D_ResourceManagerBase<F3D_Mesh>* meshManager;

};


#endif