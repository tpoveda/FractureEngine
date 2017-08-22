#ifndef F3D_Texture2D_H
#define F3D_Texture2D_H

#include "F3D_PixelData.h"
#include "F3D_TextureBase.h"
#include "../../Layer1/F3D_Resource.h"

class F3D_Texture2D : public F3D_TextureBase, public F3D_Resource
{
public:
	F3D_Texture2D(const F3D_Color&  color, const std::string& name, const std::string& path = "./");
	F3D_Texture2D(const std::string& name,  const std::string& path, GLint internalFormat, int width, int height, GLenum format, GLenum type, const unsigned char* pixels, unsigned int dataSize, bool mipMap, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT, float anisotropic);
	virtual ~F3D_Texture2D();

	virtual bool init();
	virtual void freePixels();
	const F3D_PixelData& getPixelData() const;

private:
	F3D_PixelData m_pixelData;
};

typedef std::shared_ptr<F3D_Texture2D> Frac3DTexture2D;

#endif