#ifndef F3D_ResourceManager_H
#define F3D_ResourceManager_H

#include "F3D_ResourceManagerBase.h"

#include "../Layer0/F3D_Singleton.h"

#include "../Layer5/F3D_Texture2DManager.h"
#include "../Layer5/F3D_MeshManager.h"

class F3D_ResourceManager : public F3D_Singleton<F3D_ResourceManager>
{
	friend class F3D_Singleton<F3D_ResourceManager>;

public:
	F3D_Texture2DManager* getTextureManager();
	F3D_MeshManager* getMeshManager();

private:
	F3D_ResourceManager();
	~F3D_ResourceManager();
	F3D_Texture2DManager* texture2DManager;
	F3D_MeshManager* meshManager;
};

#endif