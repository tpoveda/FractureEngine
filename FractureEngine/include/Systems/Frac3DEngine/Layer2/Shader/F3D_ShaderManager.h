#ifndef F3D_ShaderManager_H
#define F3D_ShaderManager_H

#include "../../_includesF3D.h"

#include "../../Layer0/F3D_Singleton.h"

#include "F3D_Shader.h"

class F3D_ShaderManager : public F3D_Singleton<F3D_ShaderManager>
{
	friend class F3D_Singleton<F3D_ShaderManager>;

public:
	//! @brief Anade un nuevo shader
	//! @param shader Shader a anadir
	void addShader(const Frac3DShader& shader);

	//! @brief Elimine un shader
	//! @param shader Shader a anadir
	void removeShader(const Frac3DShader& shader);

	//! @brief Devuelve todos los shaders
	//! @return Todos los shaders anadidos
	const std::multimap<std::string, Frac3DShader>& getAllShaders() const;

private:
	//! @brief Constructor de la clase F3D_ShaderManager
	F3D_ShaderManager();

	//! @brief Destructor de la clase F3D_ShaderManager
	virtual ~F3D_ShaderManager();

	//! @brief Lista de shaders
	std::multimap<std::string, Frac3DShader> allShaders;
};

#endif