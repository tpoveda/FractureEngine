#ifndef F3D_PixelData_H
#define F3D_PixelData_H

#include "../../_includesF3D.h"

//! @class F3D_PixelData Clase que almacena informacion de los pixeles de una imagen
class F3D_PixelData
{
public:
	//! @brief Constructor de la clase PixelData
	F3D_PixelData();

	//! @brief Constructor de la clase PixelData
	//! @param width Anchura de la imagen
	//! @param height Altura de la imagen
	//! @param format Formato de la imagen
	//! @param type Tipo de la imagen
	//! @param pixels Pixeles de la imagen
	//! @param dataSize Tamano de la imagen
	F3D_PixelData(int width, int height, GLenum format, GLenum type, const unsigned char* pixels, unsigned int dataSize);

	//! @brief Constructor de la clase PixelData
	//! @param other Clase PixelData
	F3D_PixelData(const F3D_PixelData& other);

	//! Destructor de la clase PixelData
	virtual ~F3D_PixelData();

	F3D_PixelData& operator=(const F3D_PixelData& other);

	//! Copia los pixeles de una imagen a otra
	//! @param other Pixeles a copiar
	void setPixels(const F3D_PixelData& other);

	//! @brief Elimina los pixeles de la memoria
	void freePixels();

	//! @brief Devuelve la anchura de la imagen
	//! @return Anchura de la imagen
	int getWidth() const;

	//! @brief Devuelve la altura de la imagen
	//! @return Altura de la imagen
	int getHeight() const;

	//! @brief Devuelve el formato de la imagen
	//! @return Formato de la imagen
	GLenum getFromat() const;

	//! @brief Devuelve el tipo de la imagen
	//! @return Tipo de la imagen
	GLenum getType() const;

	//! @brief Devuelve los pixeles de la imagen
	//! @return Pixeles de la imagen
	unsigned char* getPixels() const;

	//! @brief Devuelve el tamano de la informacion de la imagen
	//! @return Tamano de la informacion de la imagen
	unsigned int getDataSize() const;

private:
	//! @brief Anchura de la imagen
	int m_width;

	//! @brief Altura de la imagen
	int m_height;

	//! @brief Formato de la imagen
	GLenum m_format;

	//! @brief Tipo de la imagen
	GLenum m_type;

	//! @brief Pixeles de la imagen
	unsigned char* m_pixels;

	//! @brief Tamano de la imagen
	unsigned int m_dataSize;
};

#endif