#ifndef F3D_TextureFactory_H
#define F3D_TextureFactory_H

#include "../_includesF3D.h"

#include "IL/il.h"
#include "IL/ilu.h"

#include "../Layer2/Texture/F3D_Texture2D.h"
#include "../Layer2/Texture/F3D_TextureCubeMap.h"

enum FormatDepth
{
	Bps8,
	Bps16,
	Bps32
};

class F3D_TextureFactory
{
public:
	F3D_TextureFactory();
	virtual ~F3D_TextureFactory();

	// Funciones de carga de texturas
	F3D_Texture2D* loadTexture2D(const std::string& name, const std::string& path, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;
	
	//Funciones de carga de cubemaps
	Frac3DTextureCubeMap loadTextureCubeMap(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap = true, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;
	Frac3DTextureCubeMap loadTextureCubeMap(const std::string& name, const std::string& path, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	//Funciones extra
	bool isAutoInternalFloat() const;
	bool isAutoInternalInt() const;
	void setAutoInternalFloat(bool autoInternalFloat);
	void setAutoInternalInt(bool autoInternalInt);
	enum FormatDepth getFloatBps() const;
	enum FormatDepth getIntBps() const;
	void setFloatBps(enum FormatDepth floatBps);
	void setIntBps(enum FormatDepth intBps);


protected:
	ILuint loadImage(const std::string& filename) const;

	bool m_autoInternalFloat;
	bool m_autoInternalInt;
	enum FormatDepth m_floatBps;
	enum FormatDepth m_intBps;
	GLenum gatherInternalFormat(GLenum format, GLenum type) const;
};



#endif