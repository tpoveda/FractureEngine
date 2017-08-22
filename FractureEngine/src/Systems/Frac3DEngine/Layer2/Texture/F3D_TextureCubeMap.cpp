#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_TextureCubeMap.h"


F3D_TextureCubeMap::F3D_TextureCubeMap(GLint internalFormat, int width, int height, GLenum format, GLenum type, const unsigned char* pixelsPosX, const unsigned char* pixelsNegX, const unsigned char* pixelsPosY, const unsigned char* pixelsNegY, const unsigned char* pixelsPosZ, const unsigned char* pixelsNegZ, unsigned dataSize, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) :
F3D_TextureBase(GL_TEXTURE_CUBE_MAP, internalFormat, width, height, format, type, dataSize, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic)
{
	pixelData[0] = F3D_PixelData(width, height, format, type, pixelsPosX, dataSize);
	pixelData[1] = F3D_PixelData(width, height, format, type, pixelsNegX, dataSize);
	pixelData[2] = F3D_PixelData(width, height, format, type, pixelsPosY, dataSize);
	pixelData[3] = F3D_PixelData(width, height, format, type, pixelsNegY, dataSize);
	pixelData[4] = F3D_PixelData(width, height, format, type, pixelsPosZ, dataSize);
	pixelData[5] = F3D_PixelData(width, height, format, type, pixelsNegZ, dataSize);

	init();
}

F3D_TextureCubeMap::~F3D_TextureCubeMap()
{
	freePixels();
}

bool F3D_TextureCubeMap::init()
{
	if (m_width < 1 || m_height < 1) return false;

	if (!m_textureName)
	{
		glGenTextures(1, &m_textureName);
		if (!m_textureName) return false;
	}

	glBindTexture(m_target, m_textureName);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, pixelData[0].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, pixelData[1].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, pixelData[2].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, pixelData[3].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, pixelData[4].getPixels());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, pixelData[5].getPixels());

	if (m_mipMap)
	{
		glGenerateMipmap(m_target);
	}

	glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_minFilter);
	glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, m_magFilter);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_S, m_wrapS);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_T, m_wrapT);

	return true;
}

void F3D_TextureCubeMap::freePixels()
{
	for (int i = 0; i < 6; i++) pixelData[i].freePixels();
}

const F3D_PixelData& F3D_TextureCubeMap::getPixelData(int index) const
{
	if (index < 0 || index > 5) throw "Indice fuera de los limites: Un cubemap tiene 6 lados (indice valor entre 0 y 5)";
	return pixelData[index];
}