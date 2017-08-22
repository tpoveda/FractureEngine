#ifndef FES_RENDER_H
#define FES_RENDER_H

#include "../Interfaces/FE_System.h"
#include "Frac3DEngine/Layer6/F3D_ResourceManager.h"
#include "Frac3DEngine/Layer6//F3D_RenderManager.h"
#include "Frac3DEngine/Layer6/F3D_EntityManager.h"

// Esta clase no actua como un sistema en si ya que no se encarga de procesar entidades de ningun, basicamente es el que inicialia
// los diferentes subistemas (que algunos si que gestionan entidades) del motor de renderizado Frac3DEngie
class FES_Render : public FE_System
{
public:
	FES_Render();
	virtual ~FES_Render();

	//! @brief Metodo que inicializa los distinstos subsistemas del sistema de render
	void init();

	void processEntities(std::vector<F3D_Entity*>) override;
	
	//! @brief Metodo que devuelve la instancia al gestor de entidades
	//! @return F3D_EntityManager* puntero al gestor de entidades
	//
	F3D_EntityManager* getEntityManager();

	//! @brief Metodo que devuelve la instancia del gestor de renderizado de la escena
	//! @return F3D_RenderManager* puntero al gestor del renderizado de la escena
	F3D_RenderManager* getRenderManager();

	//! @brief Metodo que devuelve la instancia del gestor de recursos de la escena
	//! @brief F3D_ResourceManager* puntero al gestor de recursos de la escena
	F3D_ResourceManager* getResourceManager();

private:
	F3D_EntityManager* EntityManagerPointer;
	F3D_RenderManager* RenderManagerPointer;
	F3D_ResourceManager* ResourceManagerPointer;

};


#endif