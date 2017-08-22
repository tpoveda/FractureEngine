#ifndef _GLOBALVARS_H
#define _GLOBALVARS_H

#include <string>

/*
Archivo de cabecera para incluir variables globales y tenerlas
todas recogidas en el mismo lugar.
Todas las enumeraciones tambien se encuentra aqui por lo que 
desde cualquier parte del codigo se podra acceder a cualquier
enumeracion para facilitarnos el trabajo.
*/


/*************************************/
/************ CONSTANTES *************/
/*************************************/
const int KNUM_SYSTEMS = 8;
const int KNUM_COMPONENTS = 20;
const int WIDTH = 1024;
const int HEIGHT = 720;
const std::string TITLE = "Last Bastion";
const bool FULLSCREEN = false;
const bool DEBUG = true;

/*************************************/
/************* SISTEMAS **************/
/*************************************/

enum system_types
{ 
/*1*/	Debug, 
/*2*/	Render,
/*3*/	Movement,
/*4*/	Input,
/*5*/	GUI,
/*6*/	Physics,
/*7*/	IA,
/*8*/	Networking
};


/*************************************/
/************ COMPONENTES ************/
/*************************************/
enum component_types
{
	Transform,														// Componentes de transformacion
	Texture, Mesh, AnimatedMesh, Heightmap, Camera,					// Componentes de render
	Move,															// Componentes de movimiento
	Input_Keyboard, Input_Mouse, Input_Joystick,					// Componentes de input
	Image, Sprite, Callback,										// Componentes de GUI
	CollisionShape, CollisionBody, CollisionObject, CollisionWorld,	// Componentes de fisica
	IABehavior,														// Componentes de IA
	NetReceiver, NetSender											// Componentes de red
};



#endif