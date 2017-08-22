#include "../../../../../include/Systems/Frac3DEngine/Layer2/Shader/F3D_ShaderFactory.h"

std::string F3D_ShaderFactory::m_path = "./res/shaders/";

F3D_ShaderFactory::F3D_ShaderFactory()
{
}

F3D_ShaderFactory::~F3D_ShaderFactory()
{
}

void F3D_ShaderFactory::setPath(const std::string& path)
{
	F3D_ShaderFactory::m_path = path;
}

const std::string& F3D_ShaderFactory::getPath()
{
	return m_path;
}

Frac3DShader F3D_ShaderFactory::createPhongShader() const
{
	Frac3DShader shader;
	return NULL;
	
}