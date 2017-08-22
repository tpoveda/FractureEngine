#ifndef FE_Game_H
#define FE_Game_H

#include "../FractureEngine.h"

class FE_Game
{
public:
	FE_Game();
	virtual ~FE_Game();

	virtual void init();
	virtual void input();
	virtual void update();
	virtual void render();

	

};



#endif