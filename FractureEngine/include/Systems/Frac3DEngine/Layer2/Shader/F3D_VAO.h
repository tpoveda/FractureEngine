#ifndef F3D_VAO_H
#define F3D_VAO_H

#include "../../_includesF3D.h"
#include "F3D_Shader.h"

//! @class F3D_VAO Clase que permite crear VAO (Vertex Attributes Objects)
class F3D_VAO
{
public:
	// Constructor de la clase VAO
	//! @param Programa del shader
	F3D_VAO(const Frac3DShader& shader);

	//! @brief Destructor de la clase VAO
	virtual ~F3D_VAO();

	//! @brief Enlaza el shader al contexto
	void bind() const;

	//! @brief Desenlaza el shader al contexto
	void unbind() const;

	//! @brief Devuelve del shader
	//! @return Shader
	const Frac3DShader& getShader() const;

protected:
	//! @brief Genera el VAO
	void generateVAO();

	//! @brief Elimina el VAO
	void deleteVAO();

	//! @brief Shader
	Frac3DShader m_shader;

	//! @brief ID del VAO
	GLuint m_vao;
};

typedef std::shared_ptr<F3D_VAO> Frac3DVAO;

#endif