#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_Texture2D.h"

F3D_Texture2D::F3D_Texture2D(const F3D_Color& color, const std::string& name, const std::string& path) :
F3D_TextureBase(GL_TEXTURE_2D, color),
F3D_Resource(-1, name, path),
m_pixelData(1, 1, GL_RGBA, GL_FLOAT, (const unsigned char*)color.getRGBA(), sizeof(color))
{
	init();
}

F3D_Texture2D::F3D_Texture2D(const std::string& name, const std::string& path, GLint internalFormat, int width, int height, GLenum format, GLenum type, const unsigned char* pixels, unsigned dataSize, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
F3D_Resource(-1, name, path),
F3D_TextureBase(GL_TEXTURE_2D, internalFormat, width, height, format, type, dataSize, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic),
m_pixelData(width, height, format, type, pixels, dataSize)
{
	init();
}

F3D_Texture2D::~F3D_Texture2D()
{
	freePixels();
}

bool F3D_Texture2D::init()
{
	if (m_width < 1 || m_height < 1)
	{
		return false;
	}

	if (!m_textureName)
	{
		glGenTextures(1, &m_textureName);
		if (!m_textureName)
		{
			return false;
		}
	}

	glBindTexture(m_target, m_textureName);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(m_target, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, m_pixelData.getPixels());

	if (m_mipMap) glGenerateMipmap(m_target);

	glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_minFilter);
	glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, m_magFilter);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_S, m_wrapS);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_T, m_wrapT);

	return true;
}

void F3D_Texture2D::freePixels()
{
	m_pixelData.freePixels();
}

const F3D_PixelData& F3D_Texture2D::getPixelData() const
{
	return m_pixelData;
}