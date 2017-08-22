#ifndef F3D_Mesh_H
#define F3D_Mesh_H

#include "../../_includesF3D.h"

#include "../../Layer1/F3D_Resource.h"

#include <Importer.hpp>
#include <scene.h>
#include <mesh.h>
#include <postprocess.h>
#include <cimport.h>

#include <glm.hpp>


//! @class F3D_Mesh Clase que gestiona el almacenamiento de modelos 3D en nuestor motor
//!
/*
	En estos momentos las mallas se componen de varias submallas, por lo tanto, al cargar un modelo
	formado por varias mallas, la carga se realiza de forma correcta.

	Actualmente no soporta el uso de varios VAOs, por lo tanto, aunque se carguen varias submallas
	las propiedades de renderizado son iguales para todas las mallas. Una mejora seria permitir que 
	cada submallas tuviese su propio VAO y que se puede renderizar cada submalla de la malla con sus
	propias propiedades (propio shader), de esta manera conseguiriamos renderizar una submalla con, por ejemplo,
	un material reflectivo y otro con un material transparente. Se implementara en futuras versiones :)

	Otra mejora a implementar esta relacionada con los mapas de UVs, ahora mismo solamente carga el mapa de UVs
	0 del modelo, lo suyo seria que se pudiesen trabajar con diferentes sets de coordenadas de texturas, para si
	aumentar la calidad de la mismas ya que, actualmente, un personaje debe texturizarse por completo (tanto ropa 
	como cabeas y extremidades) usando un unico mapa UVs (espacio 0 a 1). Si pudiesemos usar varios mapas UVs
	podriamos texturizar la cabeza en el mapa 0 y el cuerpo en el mapa 1 usando dos texturas diferentes y dos espacios UVs
	distintos con lo que conseguiriamos aumentar la caliad grafica de los visuales del juego*
*/
class F3D_Mesh : public F3D_Resource
{
public:
	F3D_Mesh(const std::string& name, const std::string& path);
	virtual ~F3D_Mesh();

	void Render() const;

	struct F3D_MeshData
	{
		static enum BUFFERS
		{
			VERTEX_BUFFER,
			TEXCOORD_BUFFER,
			NORMAL_BUFFER,
			INDEX_BUFFER,
			TANGENT_BUFFER,
			BONES_BUFFER
		};

		GLuint vao;
		GLuint vbo[6];

		unsigned int elementCount;

		F3D_MeshData(aiMesh* mesh);
		~F3D_MeshData();

		unsigned int numVertices;
		unsigned int numFaces;

		GLfloat* vertices;
		GLfloat* normals;
		GLfloat* bitangents;
		GLfloat* tangents;
		GLfloat* texCoords;
		GLuint* indices;

		void Load(aiMesh* mesh);
		void Render();
		int getNumVertices() const;
		int getNumFaces();

		void createBuffers(aiMesh* mesh);
		void fillBuffers(aiMesh* mesh);
		void calculateBuffers(aiMesh* mesh);

		void calculatePositions(aiMesh* mesh);
		void calculateNormals(aiMesh* mesh);
		void calculateTexCoords(aiMesh* mesh);
		void calculateBitangents(aiMesh* mesh);
		void calculateFaces(aiMesh* mesh);
	};
	
	int getNumMeshes() const;
	F3D_MeshData* getMesh(const unsigned int index) const;

private:
	std::vector<F3D_MeshData*> meshEntries;
	F3D_MeshData* meshData;
	int numMeshes;

	void showMeshInfo(const aiScene* scene);

};



#endif