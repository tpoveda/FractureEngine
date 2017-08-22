#ifndef FES_DEBUG_H
#define FES_DEBUG_H

#include "../interfaces/FE_System.h"


class FES_Debug : public FE_System
{

public:

	FES_Debug();
	~FES_Debug();

	void init();
	void processEntities(std::vector<F3D_Entity*>);

};


#endif