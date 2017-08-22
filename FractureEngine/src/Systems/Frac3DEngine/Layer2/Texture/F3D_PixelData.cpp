#include "../../../../../include/Systems/Frac3DEngine/Layer2/Texture/F3D_PixelData.h"

F3D_PixelData::F3D_PixelData() :
m_width(0),
m_height(0),
m_format(GL_RGB),
m_type(GL_UNSIGNED_BYTE),
m_pixels(nullptr),
m_dataSize(0)
{
}

F3D_PixelData::F3D_PixelData(int width, int height, GLenum format, GLenum type, const unsigned char* pixels, unsigned dataSize) :
m_width(width),
m_height(height),
m_format(format),
m_type(type),
m_pixels(nullptr),
m_dataSize(0)
{
	// comprobamos que la imagen tiene informacion
	if (pixels && dataSize > 0)
	{
		m_pixels = new unsigned char[dataSize];

		if (m_pixels)
		{
			memcpy(m_pixels, pixels, dataSize);
			m_dataSize = dataSize;
		}
	}
}

F3D_PixelData::F3D_PixelData(const F3D_PixelData& other)
{
	setPixels(other);
}

F3D_PixelData::~F3D_PixelData()
{
	freePixels();
}

F3D_PixelData& F3D_PixelData::operator=(const F3D_PixelData& other)
{
	setPixels(other);

	return *this;
}

void F3D_PixelData::setPixels(const F3D_PixelData& other)
{
	// comprobamos que la informacion no es la misma
	if (this != &other)
	{
		freePixels();

		m_width = other.m_width;
		m_height = other.m_height;
		m_format = other.m_format;
		m_type = other.m_type;
		if (other.m_dataSize > 0)
		{
			m_pixels = new unsigned char[other.m_dataSize];
			if (m_pixels)
			{
				memcpy(m_pixels, other.m_pixels, other.m_dataSize);
				m_dataSize = other.m_dataSize;
			}
		}
	}
}

void F3D_PixelData::freePixels()
{
	if (m_pixels)
	{
		delete[] m_pixels;
		m_pixels = nullptr;
		m_dataSize = 0;
	}
}

int F3D_PixelData::getWidth() const
{
	return m_width;
}

int F3D_PixelData::getHeight() const
{
	return m_height;
}

GLenum F3D_PixelData::getFromat() const
{
	return m_format;
}

GLenum F3D_PixelData::getType() const
{
	return m_type;
}

unsigned char* F3D_PixelData::getPixels() const
{
	return m_pixels;
}

unsigned F3D_PixelData::getDataSize() const
{
	return m_dataSize;
}