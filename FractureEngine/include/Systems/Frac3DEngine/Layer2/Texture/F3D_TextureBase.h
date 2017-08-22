#ifndef F3D_TextureBase_H
#define F3D_TextureBase_H

#include "../../Layer0/F3D_Color.h"
#include "F3D_Texture.h"

class F3D_TextureBase : public F3D_Texture
{
public:
	F3D_TextureBase(GLenum target, const F3D_Color& color);
	F3D_TextureBase(GLenum target, GLint internalFormat, int width, int height, GLenum format, GLenum type, int dataSize, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~F3D_TextureBase();

	virtual void freePixels() = 0;

	bool isMipMap() const;
	void setMipMap(bool mipMap);
	GLint getMinFilter() const;
	GLint getMagFilter() const;
	GLint getWrapS() const;
	GLint getWrapT() const;
	float getAnisotropic() const;
	GLenum getFormat() const;
	GLenum getType() const;
	void setMinFilter(GLint minFilter);
	void setMagFilter(GLint magFilter);
	void setWrapS(GLint wrapS);
	void setWrapT(GLint wrapT);
	void setAnisotropic(float level);
	void setMaxAnisotropic();

protected:
	GLenum m_format;
	GLenum m_type;
	int m_dataSize;
	bool m_mipMap;
	GLint m_minFilter;
	GLint m_magFilter;
	GLint m_wrapS;
	GLint m_wrapT;
	float m_anisotropic;
	bool m_hasAnisotropic;

	virtual void changingSize();
};


#endif