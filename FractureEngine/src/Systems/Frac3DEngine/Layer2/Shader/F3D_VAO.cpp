#include "../../../../../include/Systems/Frac3DEngine/Layer2/Shader/F3D_VAO.h"

F3D_VAO::F3D_VAO(const Frac3DShader& shader) :
m_shader(shader),
m_vao(0)
{
}

F3D_VAO::~F3D_VAO()
{
}

void F3D_VAO::bind() const
{
	glBindVertexArray(m_vao);
}

void F3D_VAO::unbind() const
{
	glBindVertexArray(0);
}

const Frac3DShader& F3D_VAO::getShader() const
{
	return m_shader;
}

void F3D_VAO::generateVAO()
{
	glGenVertexArrays(1, &m_vao);
	bind();
}

void F3D_VAO::deleteVAO()
{
	unbind();
	glDeleteVertexArrays(1, &m_vao);
}