#ifndef F3D_Texture_H
#define F3D_Texture_H

#include "../../_includesF3D.h"

class F3D_Texture
{
public:
	F3D_Texture(GLenum target, GLint internalFormat, int width, int height);
	virtual ~F3D_Texture();

	virtual bool init() = 0;
	void destroy();

	GLenum getTarget() const;
	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);
	void setWidthHeight(int width, int height);
	GLuint getTextureName() const;
	GLint getInternalFormat();
	void setInternalFormat(GLint format);

protected:
	GLenum m_target;
	GLint m_internalFormat;
	int m_width;
	int m_height;
	GLuint m_textureName;

	virtual void changingSize() = 0;
};

#endif