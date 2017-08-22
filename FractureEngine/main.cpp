#include <iostream>
#include "_includes.h"
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char* args[])
{

	/*FE_ConfigParser cfg("config.ini");

	std::cout << "Anchura de la pantalla: " << cfg.getValueOfKey<int>("width") << std::endl;
	std::cout << "Altura de la pantalla: " << cfg.getValueOfKey<int>("height") << std::endl;
	std::cout << "Titulo del juego: " << cfg.getValueOfKey<std::string>("title") << std::endl;
	std::cout << "Pantalla completa: " << cfg.getValueOfKey<bool>("fullscreen") << std::endl;
	std::cout << "Modo debug: " << cfg.getValueOfKey<bool>("debug") << std::endl;

	std::cin.get();*/

	// creacion del puntero al Fracture Engine (en este punto, los subsistemas se inicializan)
	FractureEngine* engine = new FractureEngine();

	// configuracion del motor
	engine->getRenderSystem()->getRenderManager()->getWindow()->setTitle("The Last Bastion");

	// creamos el juego The Last Bastion
	LastBastion lastBastion(engine);

	// inicio del juego
	lastBastion.init();

	delete engine;
	engine = nullptr;

	_CrtDumpMemoryLeaks();

	return 0;
}