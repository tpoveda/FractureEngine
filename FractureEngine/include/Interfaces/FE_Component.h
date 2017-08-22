#ifndef FE_Component_H
#define FE_Component_H

#include "../_globalVars.h"

class FE_Component
{
protected:
	bool enabled;
	int type;																

public:
	int getType(){ return type; };

	bool isEnabled(){ return enabled; };
	void setEnabled(bool enable) { enabled = enable; };

};

#endif