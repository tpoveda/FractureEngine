#ifndef F3D_TextureCubeMap_H
#define F3D_TextureCubeMap_H

#include "F3D_PixelData.h"
#include "F3D_TextureBase.h"

class F3D_TextureCubeMap : public F3D_TextureBase
{
public:
	F3D_TextureCubeMap(GLint internalFormat, int width, int height, GLenum format, GLenum type, const unsigned char* pixelsPosX, const unsigned  char* pixelsNegX, const unsigned char* pixelsPosY, const unsigned char* pixelsNegY, const unsigned char* pixelsPosZ, const unsigned char* pixelsNegZ, unsigned int dataSize, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~F3D_TextureCubeMap();

	virtual bool init();
	virtual void freePixels();
	const F3D_PixelData& getPixelData(int index) const;

private:
	F3D_PixelData pixelData[6];
};

typedef std::shared_ptr<F3D_TextureCubeMap> Frac3DTextureCubeMap;

#endif