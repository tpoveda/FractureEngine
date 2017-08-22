#ifndef F3D_ShaderFactory_H
#define F3D_ShaderFactory_H

#include "../../_includesF3D.h"
#include "F3D_Shader.h"

class F3D_ShaderFactory
{
public:
	F3D_ShaderFactory();
	virtual ~F3D_ShaderFactory();

	static void setPath(const std::string& path);
	static const std::string& getPath();

	Frac3DShader createPhongShader() const;

	/* AÑADIR TIPOS DE SHADERS AQUI */

private:
	static std::string m_path;
};


#endif