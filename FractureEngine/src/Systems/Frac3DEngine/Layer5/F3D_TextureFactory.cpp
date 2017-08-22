#include <iostream>
#include "../../../../include/Systems/Frac3DEngine/Layer5/F3D_TextureFactory.h"

F3D_TextureFactory::F3D_TextureFactory() :
m_autoInternalFloat(false),
m_autoInternalInt(true),
m_floatBps(Bps16),
m_intBps(Bps8)
{
	ilInit();
	iluInit();

	ilEnable(IL_CONV_PAL);
	ilEnable(IL_ORIGIN_SET);
	ilEnable(IL_ORIGIN_LOWER_LEFT);
}

F3D_TextureFactory::~F3D_TextureFactory()
{
}

F3D_Texture2D* F3D_TextureFactory::loadTexture2D(const std::string& name, const std::string& path, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	std::string id;
	ILuint imageName = loadImage(path+name);

	if (imageName)
	{
		ILinfo imageInfo;
		iluGetImageInfo(&imageInfo);

		printf("Creando la textura %s\n", path+name.c_str());

		F3D_Texture2D* texture2D = new F3D_Texture2D(name, path, gatherInternalFormat(imageInfo.Format, imageInfo.Type), imageInfo.Width, imageInfo.Height, imageInfo.Format, imageInfo.Type, imageInfo.Data, imageInfo.SizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic);

		ilBindImage(0);
		ilDeleteImages(1, &imageName);

		return texture2D;
	}

	return NULL;
}

ILuint F3D_TextureFactory::loadImage(const std::string& filename) const
{
	ILuint imageName = 0;
	std::string strippedFilename = filename;
	ILint found;

	ilGenImages(1, &imageName);
	ilBindImage(imageName);

	ILboolean success = ilLoadImage((const ILstring)strippedFilename.c_str());

	if (!success)
	{
		found = strippedFilename.find_last_of("/");
		if (found != -1)
		{
			strippedFilename = strippedFilename.substr(found + 1);
			success = ilLoadImage((const ILstring)strippedFilename.c_str());
		}
		else
		{
			found = strippedFilename.find_last_of("\\");
			if (found != -1)
			{
				strippedFilename = strippedFilename.substr(found + 1);
				success = ilLoadImage((const ILstring)strippedFilename.c_str());
			}
		}
	}

	if (success)
	{
		ILinfo imageInfo;
		iluGetImageInfo(&imageInfo);

		if (imageInfo.Type != IL_FLOAT && imageInfo.Type != IL_UNSIGNED_BYTE)
		{
			if (imageInfo.Type == IL_DOUBLE || imageInfo.Type == IL_HALF)
			{
				ilConvertImage(imageInfo.Format, IL_FLOAT);
			}
			else ilConvertImage(imageInfo.Format, IL_UNSIGNED_BYTE);
		}

		if (imageInfo.Format == IL_BGR)
		{
			ilConvertImage(IL_RGB, imageInfo.Type);
		}
		else if (imageInfo.Format == IL_BGRA)
		{
			ilConvertImage(IL_RGBA, imageInfo.Type);
		}

		found = strippedFilename.find_last_of(".");

		return imageName;
	}
	else
	{
		ilBindImage(0);
		ilDeleteImages(1, &imageName);

		printf("ERROR: No se ha encontrado la textura %s\n", strippedFilename.c_str());
	}

	return 0;
}

Frac3DTextureCubeMap F3D_TextureFactory::loadTextureCubeMap(const std::string& posX, const std::string& negX, const std::string& posY, const std::string& negY, const std::string& posZ, const std::string& negZ, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	Frac3DTextureCubeMap textureCubeMap;

	ILuint imageName[6];
	ILinfo imageInfo[6];

	for (GLenum cubeMapSide = GL_TEXTURE_CUBE_MAP_POSITIVE_X; cubeMapSide <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; cubeMapSide++)
	{
		std::string filename;

		switch (cubeMapSide)
		{
		case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
			filename = posX;
			break;
		case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
			filename = negX;
			break;
		case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
			filename = posY;
			break;
		case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
			filename = negY;
			break;
		case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
			filename = posZ;
			break;
		case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
			filename = negZ;
			break;
		}


		imageName[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X] = loadImage(filename);

		if (imageName[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X])
		{
			iluGetImageInfo(&imageInfo[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X]);

			if (cubeMapSide > GL_TEXTURE_CUBE_MAP_POSITIVE_X)
			{
				if (imageInfo[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].SizeOfData != imageInfo[cubeMapSide - 1 - GL_TEXTURE_CUBE_MAP_POSITIVE_X].SizeOfData)
				{
					ilBindImage(0);
					ilDeleteImages(cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X, imageName);

					return textureCubeMap;
				}
			}
		}
		else
		{
			if (cubeMapSide > GL_TEXTURE_CUBE_MAP_POSITIVE_X)
			{
				ilBindImage(0);
				ilDeleteImages(cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X, imageName);
			}

			return textureCubeMap;
		}
	}

	//printf("Creando la textura del cubemap: %s\n", id.c_str());

	textureCubeMap = Frac3DTextureCubeMap(new F3D_TextureCubeMap(gatherInternalFormat(imageInfo[0].Format, imageInfo[0].Type), imageInfo[0].Width, imageInfo[0].Height, imageInfo[0].Format, imageInfo[0].Type, imageInfo[0].Data, imageInfo[1].Data, imageInfo[2].Data, imageInfo[3].Data, imageInfo[4].Data, imageInfo[5].Data, imageInfo[0].SizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

	ilBindImage(0);
	ilDeleteImages(6, imageName);

	return textureCubeMap;
}

Frac3DTextureCubeMap F3D_TextureFactory::loadTextureCubeMap(const std::string& name, const std::string& path, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic) const
{
	Frac3DTextureCubeMap textureCubeMap;

	ILinfo imageInfo[6];
	ILuint imageName = loadImage(path+name);

	if (imageName)
	{
		GLint activeFace = 0;

		for (GLenum cubeMapSide = GL_TEXTURE_CUBE_MAP_POSITIVE_X; cubeMapSide <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; cubeMapSide++)
		{
			ilBindImage(imageName);
			ilActiveFace(activeFace);
			if (activeFace < 2 || activeFace > 3)
			{
				iluMirror();
				iluFlipImage();
			}

			iluGetImageInfo(&imageInfo[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X]);

			if (cubeMapSide > GL_TEXTURE_CUBE_MAP_POSITIVE_X)
			{
				if (imageInfo[cubeMapSide - GL_TEXTURE_CUBE_MAP_POSITIVE_X].SizeOfData != imageInfo[cubeMapSide - 1 - GL_TEXTURE_CUBE_MAP_POSITIVE_X].SizeOfData)
				{
					ilBindImage(0);
					ilDeleteImages(1, &imageName);

					return textureCubeMap;
				}
			}

			activeFace++;

			// intercambiamos las caras para los ejes Z
			if (activeFace == 4) activeFace = 5;
			else if (activeFace == 5) activeFace = 6;
			else if (activeFace == 6) activeFace = 4;
		}

		//printf("Creando la textura del cubemap: %s\n", id.c_str());

		textureCubeMap = Frac3DTextureCubeMap(new F3D_TextureCubeMap(gatherInternalFormat(imageInfo[0].Format, imageInfo[0].Type), imageInfo[0].Width, imageInfo[0].Height, imageInfo[0].Format, imageInfo[0].Type, imageInfo[0].Data, imageInfo[1].Data, imageInfo[2].Data, imageInfo[3].Data, imageInfo[4].Data, imageInfo[5].Data, imageInfo[0].SizeOfData, mipMap, minFilter, magFilter, wrapS, wrapT, anisotropic));

		ilBindImage(0);
		ilDeleteImages(6, &imageName);
	}
	return textureCubeMap;
}

bool F3D_TextureFactory::isAutoInternalFloat() const
{
	return m_autoInternalFloat;
}

bool F3D_TextureFactory::isAutoInternalInt() const
{
	return m_autoInternalInt;
}

void F3D_TextureFactory::setAutoInternalFloat(bool autoInternalFloat)
{
	m_autoInternalFloat = autoInternalFloat;
}

void F3D_TextureFactory::setAutoInternalInt(bool autoInternalInt)
{
	m_autoInternalInt = autoInternalInt;
}

FormatDepth F3D_TextureFactory::getFloatBps() const
{
	return m_floatBps;
}

FormatDepth F3D_TextureFactory::getIntBps() const
{
	return m_intBps;
}

void F3D_TextureFactory::setFloatBps(FormatDepth floatBps)
{
	m_floatBps = floatBps;
}

void F3D_TextureFactory::setIntBps(FormatDepth intBps)
{
	m_intBps = intBps;
}

GLenum F3D_TextureFactory::gatherInternalFormat(GLenum format, GLenum type) const
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