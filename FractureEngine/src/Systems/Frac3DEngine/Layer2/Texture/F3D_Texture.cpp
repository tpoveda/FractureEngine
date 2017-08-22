#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_Texture.h"

F3D_Texture::F3D_Texture(GLenum target, GLint internalFormat, int width, int height) :
m_target(target),
m_internalFormat(internalFormat),
m_width(width),
m_height(height),
m_textureName(0)
{
}

F3D_Texture::~F3D_Texture()
{
	destroy();
}

void F3D_Texture::destroy()
{
	glBindTexture(m_target, 0);

	if (m_textureName)
	{
		glDeleteTextures(1, &m_textureName);
		m_textureName = 0;
	}
}

GLenum F3D_Texture::getTarget() const
{
	return m_target;
}

int F3D_Texture::getWidth() const
{
	return m_width;
}

int F3D_Texture::getHeight() const
{
	return m_height;
}

void F3D_Texture::setWidth(int width)
{
	if (width != m_width)
	{
		destroy();
		changingSize();
		m_width = width;
		init();
	}
}

void F3D_Texture::setHeight(int height)
{
	if (height != m_height)
	{
		destroy();
		changingSize();
		m_height = height;
		init();
	}
}

void F3D_Texture::setWidthHeight(int width, int height)
{
	if (width != m_width || height != m_height)
	{
		destroy();
		changingSize();
		m_width = width;
		m_height = height;
		init();
	}
}

GLuint F3D_Texture::getTextureName() const
{
	return m_textureName;
}

GLint F3D_Texture::getInternalFormat()
{
	return m_internalFormat;
}

void F3D_Texture::setInternalFormat(GLint format)
{
	if (m_internalFormat != format)
	{
		destroy();
		m_internalFormat = format;
		init();
	}
}