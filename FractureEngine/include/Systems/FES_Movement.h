#ifndef FES_MOVEMENT_H
#define FES_MOVEMENT_H

#include "../interfaces/FE_System.h"


class FES_Movement : public FE_System
{

public:

	FES_Movement();
	~FES_Movement();

	void init();
	void processEntities(std::vector<F3D_Entity*>);

};


#endif