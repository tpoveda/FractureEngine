#ifndef FES_GUI_H
#define FES_GUI_H

#include "../interfaces/FE_System.h"


class FES_GUI : public FE_System
{

public:

	FES_GUI();
	~FES_GUI();

	void init();
	void processEntities(std::vector<F3D_Entity*>);

};


#endif