#include "../../../../../include/Systems/Frac3DEngine/Layer2/Mesh/F3D_Mesh.h"

F3D_Mesh::F3D_Mesh(const std::string& name, const std::string& path) :
F3D_Resource(-1, name, path),
numMeshes(0)
{
	Assimp::Importer importer;

	const aiScene* scene = aiImportFile((path + name).c_str(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);
	if (!scene)
	{
		F3D_Debug::Frac3D_Log("ERROR: No se pudo cargar la malla: %s\n", importer.GetErrorString());
		return;
	}

	showMeshInfo(scene);

	for (int i = 0; i < scene->mNumMeshes; ++i)
	{
		meshEntries.push_back(new F3D_Mesh::F3D_MeshData(scene->mMeshes[i]));
		numMeshes++;
	}
}

F3D_Mesh::~F3D_Mesh()
{
	// Eliminamos las mallas cargadas en la escena
	for (int i = 0; i < meshEntries.size(); ++i)
	{
		delete meshEntries.at(i);
	}
	meshEntries.clear();
}

void F3D_Mesh::Render() const
{
	// Renderizamos las malals cargadas en la escena
	for (int i = 0; i < meshEntries.size(); ++i)
	{
		meshEntries.at(i)->Render();
	}
}

void F3D_Mesh::showMeshInfo(const aiScene* scene)
{
	F3D_Debug::Frac3D_Log("Esta malla esta compuesta por %s\n");
	F3D_Debug::Frac3D_Log("%i mallas\n", scene->mNumMeshes);
	
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		F3D_Debug::Frac3D_Log("- Malla %s", scene->mMeshes[i]->mName);
	}

	F3D_Debug::Frac3D_Log("%i animaciones\n", scene->mNumAnimations);
}

int F3D_Mesh::getNumMeshes() const
{
	return numMeshes;
}

F3D_Mesh::F3D_MeshData* F3D_Mesh::getMesh(const unsigned int index) const
{
	return meshEntries.at(index);
}

F3D_Mesh::F3D_MeshData::F3D_MeshData(aiMesh* mesh)
{
	// inicializamos los buffers
	vbo[VERTEX_BUFFER] = NULL;
	vbo[TEXCOORD_BUFFER] = NULL;
	vbo[NORMAL_BUFFER] = NULL;
	vbo[INDEX_BUFFER] = NULL;
	vbo[TANGENT_BUFFER] = NULL;
	vbo[BONES_BUFFER] = NULL;

	// calculamos la cantidad de elementos que vamos a renderizar
	elementCount = mesh->mNumFaces * 3;

	// generamos el VAO de la malla (MEJORA: generar un sistema de VAOS para cada subamalla de la malla)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// calculamos el numero de vertices y caras
	numVertices = mesh->mNumVertices;
	numFaces = mesh->mNumFaces;

	// cargamos la malla
	Load(mesh);

}

void F3D_Mesh::F3D_MeshData::Load(aiMesh* mesh)
{
	// reservamos memoria para los distintos elmentos de la malla
	createBuffers(mesh);

	// rellenamos los buffers de la malla (vertices, uvs, etc)
	fillBuffers(mesh);

	// leemos los distintos elementos de la malla
	calculateBuffers(mesh);
}

F3D_Mesh::F3D_MeshData::~F3D_MeshData()
{
	// Al eliminar la malla, eliminamos los buffers creados
	if (vbo[VERTEX_BUFFER])
	{
		glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
		vbo[VERTEX_BUFFER] = NULL;
	}

	if (vbo[TEXCOORD_BUFFER])
	{
		glDeleteBuffers(1, &vbo[TEXCOORD_BUFFER]);
		vbo[TEXCOORD_BUFFER] = NULL;
	}

	if (vbo[NORMAL_BUFFER])
	{
		glDeleteBuffers(1, &vbo[NORMAL_BUFFER]);
		vbo[NORMAL_BUFFER] = NULL;
	}

	if (vbo[INDEX_BUFFER])
	{
		glDeleteBuffers(1, &vbo[INDEX_BUFFER]);
		vbo[INDEX_BUFFER] = NULL;
	}

	if (vbo[BONES_BUFFER])
	{
		glDeleteBuffers(1, &vbo[BONES_BUFFER]);
		vbo[BONES_BUFFER] = NULL;
	}

	glDeleteVertexArrays(1, &vao);
}


void F3D_Mesh::F3D_MeshData::Render()
{
	// Bindeamos el VAO creado anteriormente (Especifica el layout con los atributos de la malla)
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

int F3D_Mesh::F3D_MeshData::getNumVertices() const
{
	return numVertices;
}

int F3D_Mesh::F3D_MeshData::getNumFaces()
{
	return numFaces;
}

void F3D_Mesh::F3D_MeshData::createBuffers(aiMesh* mesh)
{
	if (mesh->HasPositions())
	{
		//vertices = new GLfloat[numVertices * 3 * sizeof(GLfloat)];
		vertices = (GLfloat*)malloc(numVertices * 3 * sizeof(GLfloat));
	}
	if (mesh->HasNormals())
	{
		normals = (GLfloat*)malloc(numVertices * 3 * sizeof(GLfloat));
	}
	if (mesh->HasTextureCoords(0))		// Mapa de UVs con indice 0 (MEJORA: Poder usar varios mapas de UVs)
	{
		texCoords = (GLfloat*)malloc(numVertices * 2 * sizeof(GLfloat));
	}
	if (mesh->HasTangentsAndBitangents())
	{
		bitangents = (GLfloat*)malloc(numVertices * 4 * sizeof(GLfloat));
	}
}

void F3D_Mesh::F3D_MeshData::fillBuffers(aiMesh* mesh)
{
	for (unsigned int v_i = 0; v_i < mesh->mNumVertices; v_i++)
	{
		if (mesh->HasPositions())
		{
			const aiVector3D* vertex = &(mesh->mVertices[v_i]);
			vertices[v_i * 3] = (GLfloat)vertex->x;
			vertices[v_i * 3 + 1] = (GLfloat)vertex->y;
			vertices[v_i * 3 + 2] = (GLfloat)vertex->z;
		}
		if (mesh->HasNormals())
		{
			const aiVector3D* normal = &(mesh->mNormals[v_i]);
			normals[v_i * 3] = (GLfloat)normal->x;
			normals[v_i * 3 + 1] = (GLfloat)normal->y;
			normals[v_i * 3 + 2] = (GLfloat)normal->z;
		}
		if (mesh->HasTextureCoords(0))
		{
			const aiVector3D* uv = &(mesh->mTextureCoords[0][v_i]);
			texCoords[v_i * 2] = (GLfloat)uv->x;
			texCoords[v_i * 2 + 1] = (GLfloat)uv->y;
		}
		if (mesh->HasTangentsAndBitangents())
		{
			const aiVector3D* tangent = &(mesh->mTangents[v_i]);
			const aiVector3D* bitangent = &(mesh->mBitangents[v_i]);
			const aiVector3D* normal = &(mesh->mNormals[v_i]);

			glm::vec3 t = glm::vec3(tangent->x, tangent->y, tangent->z);
			glm::vec3 n = glm::vec3(normal->x, normal->y, normal->z);
			glm::vec3 b = glm::vec3(bitangent->x, bitangent->y, bitangent->z);

			// ortogonalizamos y normalizamos la tangente
			glm::vec3 t_i = glm::normalize(t - n * glm::dot(n, t));

			// calculamos el determinante de T, B, N matriz 3x3 por el metodo del producto escalar
			float det = (glm::dot(glm::cross(n, t), b));
			if (det < 0.0f) det = -1.0f;
			else det = 1.0f;

			// push back 4d vector for inverse tangent with determinant
			bitangents[v_i * 4] = t_i[0];
			bitangents[v_i * 4 + 1] = t_i[1];
			bitangents[v_i * 4 + 2] = t_i[2];
			bitangents[v_i * 4 + 3] = det;
		}
	}
}

void F3D_Mesh::F3D_MeshData::calculateBuffers(aiMesh* mesh)
{
	if (mesh->HasPositions())
	{
		calculatePositions(mesh);
	}
	if (mesh->HasNormals())
	{
		calculateNormals(mesh);
	}
	if (mesh->HasTextureCoords(0))
	{
		calculateTexCoords(mesh);
	}
	if (mesh->HasTangentsAndBitangents())
	{
		calculateBitangents(mesh);
	}
	if (mesh->HasFaces())
	{
		calculateFaces(mesh);
	}
}

void F3D_Mesh::F3D_MeshData::calculatePositions(aiMesh* mesh)
{
	// Generamos, Bindeamos y Rellenamos un Vertex Buffer Object (VBO) con los vertices de la malla
	glGenBuffers(1, &vbo[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	// Atributo 0 --> Posicion de los vertices de la malla
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	delete vertices;
}

void F3D_Mesh::F3D_MeshData::calculateTexCoords(aiMesh* mesh)
{
	// Generamos, Bindeamos y Rellenamos un Vertex Buffer Object (VBO) con las UVs de la malla
	glGenBuffers(1, &vbo[TEXCOORD_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORD_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, 2 * mesh->mNumVertices * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);

	// Atributo 1 --> UVs de la malla
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(1);

	delete texCoords;
}

void F3D_Mesh::F3D_MeshData::calculateNormals(aiMesh* mesh)
{
	// Generamos, Bindeamos y Rellenamos un Vertex Buffer Object (VBO) con las normales de la malla
	glGenBuffers(1, &vbo[NORMAL_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), normals, GL_STATIC_DRAW);

	// Atributo 2 --> Normales de la malla
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(2);

	delete normals;
}

void F3D_Mesh::F3D_MeshData::calculateBitangents(aiMesh* mesh)
{
	// Generamos, Bindeamos y Rellenamos un Vertex Buffer Object (VBO) con las tangentes
	glGenBuffers(1, &vbo[TANGENT_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TANGENT_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, 4 * mesh->mNumVertices * sizeof(GLfloat), bitangents, GL_STATIC_DRAW);

	// Atributo 3 --> Tangentes de la malla
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(3);

	delete bitangents;
}

void F3D_Mesh::F3D_MeshData::calculateFaces(aiMesh* mesh)
{
	// Total de indices = caras * 3 (x, y, z) --> Cada cada esta formada por 3 indices
	unsigned int *indices = new unsigned int[mesh->mNumFaces * 3];

	// Por cada cada, calculamos sus indices
	for (int i = 0; i < mesh->mNumFaces; ++i)
	{
		indices[i * 3] = mesh->mFaces[i].mIndices[0];
		indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
		indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
	}

	// Generamos, Bindeamos y Rellenamos un Vertex Buffer Object (VBO) con las indices de las caras de la malla
	glGenBuffers(1, &vbo[INDEX_BUFFER]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * mesh->mNumFaces * sizeof(GLuint), indices, GL_STATIC_DRAW);

	// Atributo 5 --> Indices de la malla
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(5);

	delete indices;
}
