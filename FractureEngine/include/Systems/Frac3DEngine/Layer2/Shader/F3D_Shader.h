#ifndef F3D_Shader_H
#define F3D_Shader_H

#include "../../_includesF3D.h"
#include <sys/stat.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

namespace Frac3DShaderType
{
	enum ShaderType
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
		COMPUTE_SHADER = GL_COMPUTE_SHADER
	};
}

class F3D_Shader
{
public:
	F3D_Shader(const std::string& id, const std::string& vertexFilename, const std::string& fragmentFilename);
	F3D_Shader(const std::string& id, const std::string& vertexFilename, const std::string& fragmentFilename, const std::string& geometryFilename);

	virtual ~F3D_Shader();
	bool createAndLinkProgram();

	void use();
	void unUse();

	void addAttribute(const std::string& attribute);
	void addUniform(const std::string& uniform);
	GLuint getAttribute(const std::string& attribute);
	GLuint getUniform(const std::string& uniform);
	GLuint operator[] (const std::string& attribute);
	GLuint operator() (const std::string& uniform);

	//virtual void UpdateUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, FractureMaterial& material, const glm::mat4& modelMatix = glm::mat4(1));

	void setUniform(const std::string& uniform, int value);
	void setUniform(const std::string& uniform, float value);
	void setUniform(const std::string& uniform, double value);
	void setUniform(const std::string& uniform, const glm::vec3& value);
	void setUniform(const std::string& uniform, const glm::dvec3& value);
	void setUniform(const std::string& uniform, const glm::mat4& value);

	void deleteShaderProgram();

	std::string getID() const;
	bool isLinked();
	bool isValidated();
	bool isUsed();
	int getTotalShaders();

	void printActiveUniforms();
	void printActiveAttribs();
	void printAddedUniforms();

private:
	bool fileExists(const std::string& filename);
	bool loadShader(Frac3DShaderType::ShaderType type, const std::string& filename);
	void loadFromString(GLenum type, const std::string& source);
	bool link();
	bool validate();

	std::string m_id;
	bool m_linked;
	bool m_validated;
	bool m_used;
	GLuint m_program;
	int m_totalShaders;
	GLuint m_shaders[6];
	std::map<std::string, GLuint> m_attributeList;
	std::map<std::string, GLuint > m_uniformLocationList;
};

typedef std::shared_ptr<F3D_Shader> Frac3DShader;

#endif