#ifndef FractureEngine_H
#define FractureEngine_H

#include <map>
#include "Interfaces/FE_System.h"
#include "Systems/_Systems.h"

class FractureEngine
{

private:
	static FractureEngine* enginePointer;

	F3D_EntityManager* EntityManagerPointer;
	std::map< int, FE_System*> systems;

public:
	FractureEngine();
	~FractureEngine();

	//! @brief Metodo que inicializa todos los sistemas y subsistemas del motor.
	//
	void initSystems();

	//! @brief Metodo que inicializa un sistema o subsistema del motor
	//! @param index int - Número del sistema o subsistema a inicializar
	//
	void initSystem(int);

	//! @brief Este metodo llama a todos los Update de cada sistema
	//
	void updateSystems();

	//! @brief Metodo para activar un sistema concreto
	//! @param index int - Numero del sistema que queremos activar
	//
	void activeSystem(int);

	//! @brief Metodo para desactivar un sistema concreto
	//! @param index int - Numero del sistema que queremos desactivar
	//
	void disableSystem(int);


	//! @brief Metodo que llama al getEntityManager del sistema de render para obtenerlo y pasarlo
	//! @return F3D_EntityManager* puntero al gestor de entidades
	//
	F3D_EntityManager* getEntityManager();

	//! @brief Metodo que devuelve un puntero al sistema de debug
	//! @return FES_Debug* puntero al sistema de debug
	//
	FES_Debug* getDebugSystem();

	//! @brief Metodo que devuelve un puntero al sistema de render
	//! @return FES_Render* puntero al sistema de render
	//
	FES_Render* getRenderSystem();

	//! @brief Metodo que devuelve un puntero al sistema de movimiento
	//! @return FES_Movement* puntero al sistema de movimiento
	//
	FES_Movement* getMovementSystem();

	//! @brief Metodo que devuelve un puntero al sistema de entrada
	//! @return FES_Input* puntero al sistema de entrada
	//
	FES_Input* getInputSystem();

	//! @brief Metodo que devuelve un puntero al sistema de GUI
	//! @return FES_GUI* puntero al sistema de GUI
	//
	FES_GUI* getGUISystem();

	//! @brief Metodo que devuelve un puntero al sistema de fisicas
	//! @return FES_Physics* puntero al sistema de fisicas
	//
	FES_Physics* getPhysicsSystem();

	//! @brief Metodo que devuelve un puntero al sistema de IA
	//! @return FES_IA* puntero al sistema de IA
	//
	FES_IA* getIASystem();

	//! @brief Metodo que devuelve un puntero al sistema de red
	//! @return FES_Networking* puntero al sistema de red
	//
	FES_Networking* getNetworkingSystem();

};


#endif