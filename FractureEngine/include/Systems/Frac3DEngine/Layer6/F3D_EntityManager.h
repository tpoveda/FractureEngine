#ifndef F3D_EntityManager_H
#define F3D_EntityManager_H

#include "../_includesF3D.h"

#include "../Layer0/F3D_Singleton.h"

#include "../Layer4/F3D_Entity.h"

class F3D_EntityManager : public F3D_Singleton<F3D_EntityManager>
{
	friend class F3D_Singleton<F3D_EntityManager>;

public:
	F3D_Entity* getEntityById(std::string);
	F3D_Entity* createEntity(std::string);
	F3D_Entity* createEntity(std::string, std::string);
	F3D_Entity* createEntity(std::string, F3D_Entity*);
	bool removeEntity(std::string);
	bool removeEntity(F3D_Entity*);

	std::vector<F3D_Entity*>  getEntitysFor(int);
private:
	F3D_EntityManager();
	~F3D_EntityManager();
	static F3D_EntityManager* entityManagerPointer;
	F3D_Entity* root;
	std::map<std::string, F3D_Entity*> entities;
};



#endif