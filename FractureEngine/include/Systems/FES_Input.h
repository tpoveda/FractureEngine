#ifndef FES_INPUT_H
#define FES_INPUT_H

#include "../interfaces/FE_System.h"


class FES_Input : public FE_System
{

public:

	FES_Input();
	~FES_Input();

	void init();
	void processEntities(std::vector<F3D_Entity*>);

};


#endif