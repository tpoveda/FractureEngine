#ifndef F3D_TextureFactory_H
#define F3D_TextureFactory_H

#include "IL/il.h"
#include "IL/ilu.h"

#include "F3D_TextureFactoryBase.h"

class F3D_TextureFactory : public F3D_TextureFactoryBase
{
public:
	F3D_TextureFactory();
	virtual ~F3D_TextureFactory();

	virtual Frac3DTexture2D loadTexture2D(const std::string& filename, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;
	virtual Frac3DTextureCubeMap loadTextureCubeMap(const std::string& id, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap = true, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;
	virtual Frac3DTextureCubeMap loadTextureCubeMap(const std::string& filename, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

protected:
	ILuint loadImage(const std::string& filename, std::string& id) const;
};



#endif