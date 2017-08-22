#include "../../../../../include/Systems/Frac3DEngine/Layer2/Shader/F3D_ShaderManager.h"

F3D_ShaderManager::F3D_ShaderManager() :
F3D_Singleton<F3D_ShaderManager>(), allShaders()
{

}

F3D_ShaderManager::~F3D_ShaderManager()
{
	std::multimap<std::string, Frac3DShader>::iterator it = allShaders.begin();
	while (it != allShaders.end())
	{
		it->second.reset();
		it++;
	}
	allShaders.clear();
}

void F3D_ShaderManager::addShader(const Frac3DShader& shader)
{
	allShaders.insert(std::pair<std::string, Frac3DShader>(shader->getID(), shader));
}

void F3D_ShaderManager::removeShader(const Frac3DShader& shader)
{
	std::multimap<std::string, Frac3DShader>::iterator it = allShaders.find(shader->getID());

	while (it != allShaders.end())
	{
		if (it->second == shader)
		{
			allShaders.erase(it);
			return;
		}
		it++;
	}
}

const std::multimap<std::string, Frac3DShader>& F3D_ShaderManager::getAllShaders() const
{
	return allShaders;
}