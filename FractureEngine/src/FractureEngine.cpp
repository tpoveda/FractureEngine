#include "../include/FractureEngine.h"

FractureEngine::FractureEngine()
{
	systems = decltype(systems)
	{
		{ std::pair<int, FE_System*>(Debug, new FES_Debug()) },
		{ std::pair<int, FE_System*>(Render, new FES_Render()) },
		{ std::pair<int, FE_System*>(Movement, new FES_Movement()) },
		{ std::pair<int, FE_System*>(Input, new FES_Input()) },
		{ std::pair<int, FE_System*>(GUI, new FES_GUI()) },
		{ std::pair<int, FE_System*>(Physics, new FES_Physics()) },
		{ std::pair<int, FE_System*>(IA, new FES_IA()) },
		{ std::pair<int, FE_System*>(Networking, new FES_Networking()) }
	};

	initSystems();
}


FractureEngine::~FractureEngine()
{
	// Se eliminan todos los sistemas que hemos creado.
	for (std::map< int, FE_System*>::iterator it = systems.begin(); it != systems.end(); ++it)
	{
		delete((*it).second);
		(*it).second = NULL;
	}
	systems.clear();
}

void FractureEngine::initSystems()
{
	for (int i = 0; i < KNUM_SYSTEMS; i++)
	{
		initSystem(i);
	}

	EntityManagerPointer = getRenderSystem()->getEntityManager();;
}


void FractureEngine::initSystem(int index)
{
	systems[index]->init();

	if (index == Render)
	{
		EntityManagerPointer = getRenderSystem()->getEntityManager();;
	}
}

void FractureEngine::updateSystems()
{
	for (int i = 0; i < KNUM_SYSTEMS; i++){
		if (systems[i]->isEnabled())
			systems[i]->processEntities(EntityManagerPointer->getEntitysFor(i));
	}
}

void FractureEngine::activeSystem(int index)
{
	systems[index]->setEnable(true);
}


void FractureEngine::disableSystem(int index)
{
	systems[index]->setEnable(false);
}



F3D_EntityManager* FractureEngine::getEntityManager()
{
	return EntityManagerPointer;
}

FES_Debug* FractureEngine::getDebugSystem()
{
	return (FES_Debug*)systems[Debug];
}


FES_Render* FractureEngine::getRenderSystem()
{
	return (FES_Render*)systems[Render];
}


FES_Movement* FractureEngine::getMovementSystem()
{
	return (FES_Movement*)systems[Movement];
}


FES_Input* FractureEngine::getInputSystem()
{
	return (FES_Input*)systems[Input];
}


FES_GUI* FractureEngine::getGUISystem()
{
	return (FES_GUI*)systems[GUI];
}

FES_Physics* FractureEngine::getPhysicsSystem()
{
	return (FES_Physics*)systems[Physics];
}

FES_IA* FractureEngine::getIASystem()
{
	return (FES_IA*)systems[IA];
}


FES_Networking* FractureEngine::getNetworkingSystem()
{
	return (FES_Networking*)systems[Networking];
}

