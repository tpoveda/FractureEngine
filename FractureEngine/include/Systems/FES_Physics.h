#ifndef FES_PHYSICS_H
#define FES_PHYSICS_H

#include "../interfaces/FE_System.h"


class FES_Physics : public FE_System
{

public:

	FES_Physics();
	~FES_Physics();

	void init();
	void processEntities(std::vector<F3D_Entity*>);

};


#endif