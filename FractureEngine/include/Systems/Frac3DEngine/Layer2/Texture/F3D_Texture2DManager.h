#ifndef F3D_Texture2DManager_H
#define F3D_Texture2DManager_H

#include "../../_includesF3D.h"

#include "../../Layer0/F3D_Singleton.h"
#include "../../Layer0/F3D_KeyValueMap.h"

#include "F3D_Texture2D.h"

class F3D_Texture2DManager : public F3D_Singleton<F3D_Texture2DManager>
{
	friend class F3D_Singleton <F3D_Texture2DManager>;

public:
	void addTexture(const std::string& key, const Frac3DTexture2D& texture);

	Frac3DTexture2D createTexture(const std::string& filename, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);
	Frac3DTexture2D createTexture(const std::string& key, int width, int height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);
	Frac3DTexture2D createTexture(const std::string& key, GLint internalFormat, int width, int height, GLenum format, GLenum type, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);
	Frac3DTexture2D createTexture(const std::string& key, GLint internalFormat, int width, int height, GLenum format, GLenum type, const unsigned char* pixels, unsigned int dataSize, bool mipMap = true, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR, GLint magFilter = GL_LINEAR, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT, float anisotropic = 1.0f);
private:
	F3D_Texture2DManager();
	virtual ~F3D_Texture2DManager();
	F3D_KeyValueMap<std::string, Frac3DTexture2D> allTextures;
};

#endif