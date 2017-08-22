#ifndef F3D_Entity_H
#define F3D_Entity_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "../../../Interfaces/FE_Component.h"
#include "../../../Components/_Components.h"

class F3D_Entity
{
private:
	//! @brief descripcion del metodo
	//! @param nombreparametro descripcion
	//! @params etc .... tantos como haya
	//! @return lo que devuelve
	//
	// Descripcion larga.
	std::string id;
	std::map< int , FE_Component*> components;
	std::map<std::string , F3D_Entity*> children;
	F3D_Entity* parent;

public:

	F3D_Entity(std::string id, F3D_Entity* initParent);
	~F3D_Entity();

	bool requiredSystem[KNUM_SYSTEMS];

	std::string getId();

	bool addComponent(int);
	FE_Component* getComponent(int);
		/* Zona de getComponents por tipo de componente*/
		FEC_Transform* getComponent_Transform(int);
		FEC_Texture* F3D_Entity::getComponent_Texture();
		FEC_Mesh* F3D_Entity::getComponent_Mesh();
		FEC_AnimationMesh* F3D_Entity::getComponent_AnimatedMesh();
		FEC_Heightmap* F3D_Entity::getComponent_Heightmap();
		FEC_Camera* F3D_Entity::getComponent_Camera();
		FEC_Move* F3D_Entity::getComponent_Move();
		FEC_Keyboard* F3D_Entity::getComponent_Keyboard();
		FEC_Mouse* F3D_Entity::getComponent_Mouse();
		FEC_Joystick* F3D_Entity::getComponent_Joystick();
		FEC_Image* F3D_Entity::getComponent_Image();
		FEC_Sprite* F3D_Entity::getComponent_Sprite();
		FEC_Callback* F3D_Entity::getComponent_Callback();
		FEC_CollisionShapeType* F3D_Entity::getComponent_CollisionShape();
		FEC_CollisionBodyType* F3D_Entity::getComponent_CollisionBody();
		FEC_CollisionObjectType* F3D_Entity::getComponent_CollisionObject();
		FEC_CollisionWorldType* F3D_Entity::getComponent_CollisionWorld();
		FEC_IABehaviorType* F3D_Entity::getComponent_IABehavior();
		FEC_NetReceiver* F3D_Entity::getComponent_NetReceiver();
		FEC_NetSender* F3D_Entity::getComponent_NetSender();
	bool removeComponent(int);

	bool addChild(F3D_Entity*);
	bool addChildren(std::vector<F3D_Entity*>);
	bool removeChild(std::string); // Se desvincula al hijo del padre y para no dejarlo colgado, se hace que penda de root

	std::vector<F3D_Entity*> getAll();
	std::vector<F3D_Entity*> getChildren();
	std::vector<F3D_Entity*> getBrothers();
	std::vector<F3D_Entity*> getBrothersWithoutMe();

	void setParent(F3D_Entity*);
	F3D_Entity* getParent();

	FE_Component* newComponentByType(int);

	void checkSystems();

};


#endif