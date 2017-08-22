#include <iostream>
#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_TextureFactoryBase.h"

F3D_TextureFactoryBase::F3D_TextureFactoryBase() :
m_autoInternalFloat(false),
m_autoInternalInt(true),
m_floatBps(Bps16),
m_intBps(Bps8)
{
}

F3D_TextureFactoryBase::~F3D_TextureFactoryBase()
{
}

Frac3DTexture2D F3D_TextureFactoryBase::createTexture2D(const std::string& id, int width, int height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Frac3DTexture2D(new F3D_Texture2D(id, gatherInternalFormat(format, type), width, height, format, type, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Frac3DTexture2D F3D_TextureFactoryBase::createTexture2D(const std::string& id, GLint internalFormat, int width, int height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Frac3DTexture2D(new F3D_Texture2D(id, internalFormat, width, height, format, type, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Frac3DTextureCubeMap F3D_TextureFactoryBase::createTextureCubeMap(const std::string& id, int width, int height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Frac3DTextureCubeMap(new F3D_TextureCubeMap(id, gatherInternalFormat(format, type), width, height, format, type, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Frac3DTextureCubeMap F3D_TextureFactoryBase::createTextureCubeMap(const std::string& id, GLint internalFormat, int width, int height, GLenum format, GLenum type, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Frac3DTextureCubeMap(new F3D_TextureCubeMap(id, internalFormat, width, height, format, type, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

Frac3DTexture2D F3D_TextureFactoryBase::createTexture2D(const std::string& id, GLint internalFormat, int width, int height, GLenum format, GLenum type, const unsigned char* pixels, unsigned dataSize, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	return Frac3DTexture2D(new F3D_Texture2D(id, internalFormat, width, height, format, type, pixels, dataSize, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));
}

bool F3D_TextureFactoryBase::isAutoInternalFloat() const
{
	return m_autoInternalFloat;
}

bool F3D_TextureFactoryBase::isAutoInternalInt() const
{
	return m_autoInternalInt;
}

void F3D_TextureFactoryBase::setAutoInternalFloat(bool autoInternalFloat)
{
	m_autoInternalFloat = autoInternalFloat;
}

void F3D_TextureFactoryBase::setAutoInternalInt(bool autoInternalInt)
{
	m_autoInternalInt = autoInternalInt;
}

FormatDepth F3D_TextureFactoryBase::getFloatBps() const
{
	return m_floatBps;
}

FormatDepth F3D_TextureFactoryBase::getIntBps() const
{
	return m_intBps;
}

void F3D_TextureFactoryBase::setFloatBps(FormatDepth floatBps)
{
	m_floatBps = floatBps;
}

void F3D_TextureFactoryBase::setIntBps(FormatDepth intBps)
{
	m_intBps = intBps;
}

GLenum F3D_TextureFactoryBase::gatherInternalFormat(GLenum format, GLenum type) const
{
	if (type == GL_FLOAT || type == GL_HALF_FLOAT)
	{
		if (m_autoInternalFloat) return format;

		if (format == GL_RGB)
		{
			switch (m_floatBps)
			{
			case Bps8:
				std::cout << "ERROR: No existe un formato interno de coma flotante de 8 bits. Se usara el formato automtico" << std::endl;
				break;
			case Bps16:
				return GL_RGB16F;
				break;
			case Bps32:
				return GL_RGB32F;
				break;
			}
			return GL_RGB;
		}
		else if (format == GL_RGBA)
		{
			switch (m_floatBps)
			{
			case Bps8:
				std::cout << "ERROR: No existe un formato interno de coma flotante de 8 bits. Se usara el formato automtico" << std::endl;
				break;
			case Bps16:
				return GL_RGBA16F;
				break;
			case Bps32:
				return GL_RGBA32F;
				break;
			}
			return GL_RGBA;
		}
		return format;
	}

	if (m_autoInternalInt) return format;

	if (format == GL_RGB)
	{
		switch (m_intBps)
		{
		case Bps8:
			return GL_RGB8;
			break;
		case Bps16:
			return GL_RGB16;
			break;
		case Bps32:
			if (type == GL_BYTE || type == GL_SHORT || type == GL_INT)
			{
				return GL_RGB32I;
			}
			else return GL_RGB32UI;
			break;
		}
		return GL_RGB;
	}
	else if (format == GL_RGBA)
	{
		switch (m_intBps)
		{
		case Bps8:
			return GL_RGBA8;
			break;
		case Bps16:
			return GL_RGBA16;
			break;
		case Bps32:
			if (type == GL_BYTE || type == GL_SHORT || type == GL_INT)
			{
				return GL_RGBA32I;
			}
			else return GL_RGBA32UI;
			break;
		}
		return GL_RGBA;
	}
	return format;
}