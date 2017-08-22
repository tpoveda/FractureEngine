#ifndef F3D_Texture2DManager_H
#define F3D_Texture2DManager_H

#include "../_includesF3D.h"

#include "../Layer2/Texture/F3D_Texture2D.h"
#include "../Layer6/F3D_ResourceManagerBase.h"

class F3D_Texture2DManager
{
public:
	F3D_Texture2DManager();
	virtual ~F3D_Texture2DManager();

	unsigned int createTexture(const std::string& name, const std::string& path, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);
	F3D_Texture2D* getTexture(unsigned int GUID);
	void removeTexture(unsigned int GUID);

private:
	F3D_ResourceManagerBase<F3D_Texture2D>* texture2DManager;
};

#endif