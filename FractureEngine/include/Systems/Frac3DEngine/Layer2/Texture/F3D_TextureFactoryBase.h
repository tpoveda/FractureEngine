#ifndef F3D_TextureFactoryBase_H
#define F3D_TextureFactoryBase_H

#include "../../_includesF3D.h"

#include "F3D_Texture2D.h"
#include "F3D_TextureCubeMap.h"

enum FormatDepth
{
	Bps8,
	Bps16,
	Bps32
};

class F3D_TextureFactoryBase
{
public:
	F3D_TextureFactoryBase();
	virtual ~F3D_TextureFactoryBase();

	virtual Frac3DTexture2D loadTexture2D(const std::string& filename, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const = 0;
	Frac3DTexture2D createTexture2D(const std::string& id, int width, int height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR_MIPMAP_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f)  const;
	Frac3DTexture2D createTexture2D(const std::string& id, GLint internalFormat, int width, int height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f) const;
	Frac3DTexture2D createTexture2D(const std::string& id, GLint internalFormat, int width, int height, GLenum format, GLenum type, const unsigned char* pixels, unsigned int dataSize, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = .10f) const;

	virtual Frac3DTextureCubeMap loadTextureCubeMap(const std::string& id, const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const = 0;
	virtual Frac3DTextureCubeMap loadTextureCubeMap(const std::string& filename, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const = 0;
	Frac3DTextureCubeMap createTextureCubeMap(const std::string& id, int width, int height, GLenum format, GLenum type, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;
	Frac3DTextureCubeMap createTextureCubeMap(const std::string& id, GLint internalFormat, int width, int height, GLenum format, GLenum type, bool mipMap = false, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE, float anisotropic = 1.0f) const;

	bool isAutoInternalFloat() const;
	bool isAutoInternalInt() const;
	void setAutoInternalFloat(bool autoInternalFloat);
	void setAutoInternalInt(bool autoInternalInt);

	enum FormatDepth getFloatBps() const;
	enum FormatDepth getIntBps() const;
	void setFloatBps(enum FormatDepth floatBps);
	void setIntBps(enum FormatDepth intBps);
protected:
	bool m_autoInternalFloat;
	bool m_autoInternalInt;

	enum FormatDepth m_floatBps;
	enum FormatDepth m_intBps;

	GLenum gatherInternalFormat(GLenum format, GLenum type) const;
};

#endif