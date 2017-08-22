#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_TextureBase.h"

F3D_TextureBase::F3D_TextureBase(GLenum target, const F3D_Color& color) :
F3D_Texture(target, GL_R32F, 1, 1),
m_format(GL_RED),
m_type(GL_FLOAT),
m_dataSize(sizeof(color)),
m_mipMap(false),
m_minFilter(GL_NEAREST),
m_magFilter(GL_NEAREST),
m_wrapS(GL_REPEAT),
m_wrapT(GL_REPEAT),
m_anisotropic(1.0)
{
	m_hasAnisotropic = GLEW_EXT_texture_filter_anisotropic ? true : false;

	setAnisotropic(false);
}

F3D_TextureBase::F3D_TextureBase(GLenum target, GLint internalFormat, int width, int height, GLenum format, GLenum type, int dataSize, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
F3D_Texture(target, internalFormat, width, height),
m_format(format),
m_type(type),
m_dataSize(dataSize),
m_mipMap(mipMap),
m_minFilter(minFilter),
m_magFilter(magFilter),
m_wrapS(wrapS),
m_wrapT(wrapT),
m_anisotropic(anisotropic)
{
	m_hasAnisotropic = GLEW_EXT_texture_filter_anisotropic ? true : false;

	setAnisotropic(false);
}

F3D_TextureBase::~F3D_TextureBase()
{
	std::cout << "Eliminando textura base ..." << std::endl;
}

bool F3D_TextureBase::isMipMap() const
{
	return m_mipMap;
}

void F3D_TextureBase::setMipMap(bool mipMap)
{
	if (m_mipMap != mipMap)
	{
		destroy();
		m_mipMap = mipMap;
		init();
	}
}

GLint F3D_TextureBase::getMinFilter() const
{
	return m_minFilter;
}

GLint F3D_TextureBase::getMagFilter() const
{
	return m_magFilter;
}

GLint F3D_TextureBase::getWrapS() const
{
	return m_wrapS;
}

GLint F3D_TextureBase::getWrapT() const
{
	return m_wrapT;
}

float F3D_TextureBase::getAnisotropic() const
{
	return m_anisotropic;
}

GLenum F3D_TextureBase::getFormat() const
{
	return m_format;
}

GLenum F3D_TextureBase::getType() const
{
	return m_type;
}

void F3D_TextureBase::setMinFilter(GLint minFilter)
{
	if (m_minFilter != minFilter)
	{
		m_minFilter = minFilter;
		glBindTexture(m_target, m_textureName);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, minFilter);
	}
}

void F3D_TextureBase::setMagFilter(GLint magFilter)
{
	if (m_magFilter != magFilter)
	{
		m_magFilter = magFilter;
		glBindTexture(m_target, m_textureName);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, magFilter);
	}
}

void F3D_TextureBase::setWrapS(GLint wrapS)
{
	if (m_wrapS != wrapS)
	{
		m_wrapS = wrapS;
		glBindTexture(m_target, m_textureName);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrapS);
	}
}

void F3D_TextureBase::setWrapT(GLint wrapT)
{
	if (m_wrapT != wrapT)
	{
		m_wrapT = wrapT;
		glBindTexture(m_target, m_textureName);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrapT);
	}
}

void F3D_TextureBase::setAnisotropic(float level)
{
	if (m_hasAnisotropic)
	{
		float max = 1.0f;
		if (level < 1.0f) level = 1.0f;

		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max);

		if (level > max) level = max;

		glBindTexture(m_target, m_textureName);
		glTexParameterf(m_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, level);
	}
}

void F3D_TextureBase::setMaxAnisotropic()
{
	if (m_hasAnisotropic)
	{
		float max = 1.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max);
		setAnisotropic(max);
	}
}

void F3D_TextureBase::changingSize()
{
	freePixels();
}