#ifndef FE_System_H
#define FE_System_H

#include <vector>
#include "../_globalVars.h"
#include "../Systems/Frac3DEngine/Layer4/F3D_Entity.h"

class FE_System
{

protected:
	bool enabled;
	int id;

public:

	bool isEnabled() { return enabled; };
	void setEnable(bool enable) { enabled = enable; };

	virtual void init() = 0;
	virtual void processEntities(std::vector<F3D_Entity*>) = 0;

};



#endif