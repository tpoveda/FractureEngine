#include "../../../../../include/Systems/Frac3DEngine/Layer0/F3D_Debug.h"
#include "../../../../../include/Systems/Frac3DEngine/Layer2/Shader/F3D_Shader.h"

F3D_Shader::F3D_Shader(const std::string& id, const std::string& vertexFilename, const std::string& fragmentFilename) :
m_totalShaders(0),
m_linked(false),
m_validated(false),
m_used(false),
m_program(-1)
{
	// inicializamos todas las variables del shader
	m_shaders[Frac3DShaderType::VERTEX_SHADER] = 0;
	m_shaders[Frac3DShaderType::FRAGMENT_SHADER] = 0;
	m_shaders[Frac3DShaderType::GEOMETRY_SHADER] = 0;
	m_shaders[Frac3DShaderType::COMPUTE_SHADER] = 0;
	m_shaders[Frac3DShaderType::TESS_EVALUATION_SHADER] = 0;
	m_shaders[Frac3DShaderType::TESS_CONTROL_SHADER] = 0;
	m_attributeList.clear();
	m_uniformLocationList.clear();

	m_id = id;
	loadShader(Frac3DShaderType::VERTEX_SHADER, vertexFilename);
	loadShader(Frac3DShaderType::FRAGMENT_SHADER, fragmentFilename);
	createAndLinkProgram();
}

F3D_Shader::F3D_Shader(const std::string& id, const std::string& vertexFilename, const std::string& fragmentFilename, const std::string& geometryFilename)
{
	// inicializamos todas las variables del shader
	m_shaders[Frac3DShaderType::VERTEX_SHADER] = 0;
	m_shaders[Frac3DShaderType::FRAGMENT_SHADER] = 0;
	m_shaders[Frac3DShaderType::GEOMETRY_SHADER] = 0;
	m_shaders[Frac3DShaderType::COMPUTE_SHADER] = 0;
	m_shaders[Frac3DShaderType::TESS_EVALUATION_SHADER] = 0;
	m_shaders[Frac3DShaderType::TESS_CONTROL_SHADER] = 0;
	m_attributeList.clear();
	m_uniformLocationList.clear();

	m_id = id;
	loadShader(Frac3DShaderType::VERTEX_SHADER, vertexFilename);
	loadShader(Frac3DShaderType::FRAGMENT_SHADER, fragmentFilename);
	loadShader(Frac3DShaderType::GEOMETRY_SHADER, geometryFilename);
	createAndLinkProgram();
}

F3D_Shader::~F3D_Shader()
{
	m_shaders[Frac3DShaderType::VERTEX_SHADER] = 0;
	m_shaders[Frac3DShaderType::FRAGMENT_SHADER] = 0;
	m_shaders[Frac3DShaderType::GEOMETRY_SHADER] = 0;
	m_shaders[Frac3DShaderType::COMPUTE_SHADER] = 0;
	m_shaders[Frac3DShaderType::TESS_EVALUATION_SHADER] = 0;
	m_shaders[Frac3DShaderType::TESS_CONTROL_SHADER] = 0;
	m_attributeList.clear();
	m_uniformLocationList.clear();
}

void F3D_Shader::loadFromString( GLenum type, const std::string& source)
{
	std::string tempType;
	GLuint shader;
	
	switch (type)
	{
	case Frac3DShaderType::VERTEX_SHADER:
		shader = glCreateShader(GL_VERTEX_SHADER);
		m_shaders[Frac3DShaderType::VERTEX_SHADER] = shader;
		tempType = "Vertex Shader";
		break;
	case Frac3DShaderType::FRAGMENT_SHADER:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		m_shaders[Frac3DShaderType::FRAGMENT_SHADER] = shader;
		tempType = "Fragment Shader";
		break;
	case Frac3DShaderType::GEOMETRY_SHADER:
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		m_shaders[Frac3DShaderType::GEOMETRY_SHADER] = shader;
		tempType = "Geometry Shader";
		break;
	case Frac3DShaderType::TESS_CONTROL_SHADER:
		shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		m_shaders[Frac3DShaderType::TESS_CONTROL_SHADER] = shader;
		tempType = "Control Shader";
		break;
	case Frac3DShaderType::TESS_EVALUATION_SHADER:
		shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		m_shaders[Frac3DShaderType::TESS_EVALUATION_SHADER] = shader;
		tempType = "Evaluation Shader";
		break;
	case Frac3DShaderType::COMPUTE_SHADER:
		shader = glCreateShader(GL_COMPUTE_SHADER);
		m_shaders[Frac3DShaderType::COMPUTE_SHADER] = shader;
		tempType = "Compute Shader";
		break;
	}

	//shader = glCreateShader(type);

	const char* ptmp = source.c_str();
	glShaderSource(shader, 1, &ptmp, nullptr);

	// comprobamos que el shader se ha cargado correctamente
	GLint status;
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El shader con indice %i  y de tipo %s no se pudo compilar\n", shader, tempType);
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
		fprintf(stderr, "%s: Log de compilacion para el shader %i:\n%s\n", tempType, shader, infoLog);
		F3D_Debug::Frac3D_Log("%s: Log de compilacion para el shader %i:\n%s\n", tempType, shader, infoLog);
		delete[]infoLog;
	}
	F3D_Debug::Frac3D_Log("El shader con indice %i y de tipo %s se ha compilado con exito\n", shader, tempType);
	m_totalShaders++;
}

bool F3D_Shader::loadShader(Frac3DShaderType::ShaderType type, const std::string& filename)
{
	/*if (fileExists(filename))
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El archivo %s no existe\n", filename.c_str());
		return false;
	}*/

	F3D_Debug::Frac3D_Log("Creando shader desde %s\n", filename.c_str());
	std::ifstream file;
	file.open(filename.c_str(), std::ios_base::in);
	if (file)
	{
		std::string line;
		std::string buffer;
		while (getline(file, line))
		{
			buffer.append(line);
			buffer.append("\r\n");
		}

		// copiamos a la fuente
		loadFromString(type, buffer);
	}
	else
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: No se pudo cargar el shader %s\n", filename);
		return false;
	}
	return true;
}

bool F3D_Shader::createAndLinkProgram()
{
	m_program = glCreateProgram();
	if (m_program == 0)
	{
		F3D_Debug::Frac3D_Log("ERROR: No se pudo crear el programa de shader ... \n");
		return false;
	}

	F3D_Debug::Frac3D_Log("Creado programa %u. Enlazando shaders ...\n", m_program);
	if (m_shaders[Frac3DShaderType::VERTEX_SHADER] != 0)
	{
		glAttachShader(m_program, m_shaders[Frac3DShaderType::VERTEX_SHADER]);
	}
	if (m_shaders[Frac3DShaderType::FRAGMENT_SHADER] != 0)
	{
		glAttachShader(m_program, m_shaders[Frac3DShaderType::FRAGMENT_SHADER]);
	}
	if (m_shaders[Frac3DShaderType::GEOMETRY_SHADER] != 0)
	{
		glAttachShader(m_program, m_shaders[Frac3DShaderType::GEOMETRY_SHADER]);
	}
	if (m_shaders[Frac3DShaderType::TESS_CONTROL_SHADER] != 0)
	{
		glAttachShader(m_program, m_shaders[Frac3DShaderType::TESS_CONTROL_SHADER]);
	}
	if (m_shaders[Frac3DShaderType::TESS_EVALUATION_SHADER] != 0)
	{
		glAttachShader(m_program, m_shaders[Frac3DShaderType::TESS_EVALUATION_SHADER]);
	}
	if (m_shaders[Frac3DShaderType::COMPUTE_SHADER] != 0)
	{
		glAttachShader(m_program, m_shaders[Frac3DShaderType::COMPUTE_SHADER]);
	}

	link();
	validate();

	glDeleteShader(m_shaders[Frac3DShaderType::VERTEX_SHADER]);
	glDeleteShader(m_shaders[Frac3DShaderType::FRAGMENT_SHADER]);
	glDeleteShader(m_shaders[Frac3DShaderType::GEOMETRY_SHADER]);
	glDeleteShader(m_shaders[Frac3DShaderType::TESS_CONTROL_SHADER]);
	glDeleteShader(m_shaders[Frac3DShaderType::TESS_EVALUATION_SHADER]);
	glDeleteShader(m_shaders[Frac3DShaderType::COMPUTE_SHADER]);

	return true;
}

void F3D_Shader::use()
{
	if (m_program <= 0 || (!m_linked))
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El shader no se puede usar porque no ha sido linkedado con exito\n");
		return;
	}
	glUseProgram(m_program);
	m_used = true;
}

void F3D_Shader::unUse()
{
	glUseProgram(0);
	m_used = false;
}

void F3D_Shader::addAttribute(const std::string& attribute)
{
	m_attributeList[attribute] = glGetAttribLocation(m_program, attribute.c_str());
}

void F3D_Shader::addUniform(const std::string& uniform)
{
	m_uniformLocationList[uniform] = glGetUniformLocation(m_program, uniform.c_str());
}

GLuint F3D_Shader::getAttribute(const std::string& attribute)
{
	return m_attributeList[attribute];
}

GLuint F3D_Shader::getUniform(const std::string& uniform)
{
	return m_uniformLocationList[uniform];
}

GLuint F3D_Shader::operator[](const std::string& attribute)
{
	return m_attributeList[attribute];
}

GLuint F3D_Shader::operator()(const std::string& uniform)
{
	return m_uniformLocationList[uniform];
}

void F3D_Shader::setUniform(const std::string& uniform, int value)
{
	if (m_uniformLocationList.at(uniform) >= 0) glUniform1i(m_uniformLocationList.at(uniform), value);
	else
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El uniforme %s no existe en el shader", uniform);
	}
}

void F3D_Shader::setUniform(const std::string& uniform, float value)
{
	if (m_uniformLocationList.at(uniform) >= 0) glUniform1f(m_uniformLocationList.at(uniform), value);
	else
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El uniforme %s no existe en el shader", uniform);
	}
}

void F3D_Shader::setUniform(const std::string& uniform, double value)
{
	if (m_uniformLocationList.at(uniform) >= 0) glUniform1f(m_uniformLocationList.at(uniform), value);
	else
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El uniforme %s no existe en el shader", uniform);
	}
}

void F3D_Shader::setUniform(const std::string& uniform, const glm::vec3& value)
{
	if (m_uniformLocationList.at(uniform) >= 0) glUniform3f(m_uniformLocationList.at(uniform), value.x, value.y, value.z);
	else
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El uniforme %s no existe en el shader", uniform);
	}
}

void F3D_Shader::setUniform(const std::string& uniform, const glm::dvec3& value)
{
	if (m_uniformLocationList.at(uniform) >= 0) glUniform3f(m_uniformLocationList.at(uniform), value.x, value.y, value.z);
	else
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El uniforme %s no existe en el shader", uniform);
	}
}

void F3D_Shader::setUniform(const std::string& uniform, const glm::mat4& value)
{
	if (m_uniformLocationList.at(uniform) >= 0) glUniformMatrix4fv(m_uniformLocationList.at(uniform), 1, GL_FALSE, glm::value_ptr(value));
	else
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El uniforme %s no existe en el shader", uniform);
	}
}

bool F3D_Shader::isLinked()
{
	return m_linked;
}

bool F3D_Shader::isValidated()
{
	return m_validated;
}

bool F3D_Shader::isUsed()
{
	return m_used;
}

void F3D_Shader::printActiveUniforms()
{
	GLint numActiveUniforms, size, location, maxLen;
	GLchar* name;
	GLsizei written;
	GLenum type;

	glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &numActiveUniforms);

	name = (GLchar*)malloc(maxLen);

	printf("Uniformes activos\n");
	printf("------------------------------------------------\n");
	printf(" Localizacion | Nombre\n");
	printf("------------------------------------------------\n");
	for (int i = 0; i < numActiveUniforms; ++i) {
		glGetActiveUniform(m_program, i, maxLen, &written, &size, &type, name);
		location = glGetUniformLocation(m_program, name);
		printf(" %-8d | %s\n", location, name);
	}
	printf("\n");

	free(name);
}

void F3D_Shader::printActiveAttribs()
{
	GLint numActiveAttribs, written, size, location, maxLength;
	GLenum type;
	GLchar * name;

	glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
	glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);

	name = (GLchar *)malloc(maxLength);

	printf("Atributos activos\n");
	printf("------------------------------------------------\n");
	printf(" Indice | Nombre\n");
	printf("------------------------------------------------\n");
	for (int i = 0; i < numActiveAttribs; i++) {
		glGetActiveAttrib(m_program, i, maxLength, &written, &size, &type, name);
		location = glGetAttribLocation(m_program, name);
		printf(" %-5d | %s\n", location, name);
	}
	printf("\n");

	free(name);
}

void F3D_Shader::printAddedUniforms()
{
	printf("Uniformes anadidos\n");
	printf("------------------------------------------------\n");
	std::map<std::string, GLuint>::iterator it = m_uniformLocationList.begin();

	while (it != m_uniformLocationList.end())
	{
		printf("%s\n", it->first.c_str());
		++it;
	}
	printf("------------------------------------------------\n\n");
}

int F3D_Shader::getTotalShaders()
{
	return m_totalShaders;
}

void F3D_Shader::deleteShaderProgram()
{
	glDeleteProgram(m_program);
}

std::string F3D_Shader::getID() const
{
	if (m_program <= 0)
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El shader no tiene un programa valido\n");
	};

	return m_id;
}

bool F3D_Shader::fileExists(const std::string& filename)
{
	struct stat info;
	int ret = -1;

	ret = stat(filename.c_str(), &info);
	return 0 == ret;
}

bool F3D_Shader::validate()
{
	glValidateProgram(m_program);
	GLint params = -1;
	glGetProgramiv(m_program, GL_VALIDATE_STATUS, &params);
	if (GL_TRUE != params)
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El programa con indice %i no se ha validado con exito\n\n", m_program);
		GLint infoLogLength;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(m_program, infoLogLength, nullptr, infoLog);
		fprintf(stderr, "Log de validacion del programa %i:\n%s\n", m_program, infoLog);
		F3D_Debug::Frac3D_Log("Log de validacion del programa %i:\n%s\n", m_program, infoLog);
		delete[]infoLog;
	}
	else
	{
		F3D_Debug::Frac3D_Log("El programa con indice %i se ha validado con exito\n\n", m_program);
		return true;
	}

	return false;
}

bool F3D_Shader::link()
{
	// linkeamos los shaders y comprobamos que el linkeo es correcto
	GLint status;
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		F3D_Debug::Frac3D_ErrLog("ERROR: El programa con indice %i no se pudo linkear\n", m_program);
		GLint infoLogLength;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(m_program, infoLogLength, nullptr, infoLog);
		fprintf(stderr, "Log de linkeo para el programa %i:\n%s\n", m_program, infoLog);
		F3D_Debug::Frac3D_Log("Log de linkeo para el programa %i:\n%s\n", m_program, infoLog);
		delete[]infoLog;

		m_linked = false;
	}
	else
	{
		F3D_Debug::Frac3D_Log("El programa con indice %i se ha linkeado con exito\n", m_program);
		m_linked = true;
	}

	return false;
}