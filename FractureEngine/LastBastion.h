#ifndef LastBastion_H
#define LastBastion_H

#include "include/FractureEngine.h"

class LastBastion
{
public:
	LastBastion(FractureEngine* engine);
	~LastBastion();

	void init();
	void run();
	void finish();
	void processInput();

private:
	FES_Render* frac3D;
	F3D_EntityManager* scene;
	F3D_RenderManager* render;
	F3D_ResourceManager* resource;

	FractureEngine* m_fractureEngine;
	bool m_isRunning;
};

#endif