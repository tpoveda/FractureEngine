#ifndef FES_IA_H
#define FES_IA_H

#include "../interfaces/FE_System.h"


class FES_IA : public FE_System
{

public:

	FES_IA();
	~FES_IA();

	void init();
	void processEntities(std::vector<F3D_Entity*>);

};


#endif