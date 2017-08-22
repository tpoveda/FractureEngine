#ifndef F3D_TextureCubeMapManager_H
#define F3D_TextureCubeMapManager_H

#include "../../_includesF3D.h"

#include "../../Layer0/F3D_Singleton.h"
#include "../../Layer0/F3D_KeyValueMap.h"

#include "F3D_TextureCubeMap.h"

class F3D_TextureCubeMapManager : public F3D_Singleton<F3D_TextureCubeMapManager>
{
	friend class F3D_Singleton <F3D_TextureCubeMapManager>;

public:
	void addTexture(const std::string& id, const Frac3DTextureCubeMap& texture);

	Frac3DTextureCubeMap createTexture(const std::string& id, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f);
	Frac3DTextureCubeMap createTexture(const std::string& filename, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f);
private:
	F3D_TextureCubeMapManager();
	virtual ~F3D_TextureCubeMapManager();
	F3D_KeyValueMap<std::string, Frac3DTextureCubeMap> allTextures;
};

#endif