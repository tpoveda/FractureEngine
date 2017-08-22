#ifndef F3D_Debug_H
#define F3D_Debug_H

#include "../_includesF3D.h"

#define GL_LOG_FILE "F3DLog.log"

//! @class F3D_Debug Clase que recoge algunas funciones utiles para el Debugging del motor de render
class F3D_Debug
{
public:
	F3D_Debug();
	~F3D_Debug();

	//! @brief Creamos el archivo de log
	//!
	//! Creamos el archivo de log inicial y almacenamos informacion basica como la hora y fecha de la
	//! generacion del log o la version de build
	//! @return TRUE si el archivo se ha creado correctamente o FALSE en caso contrario
	static bool Frac3D_RestartLog();

	//! @brief Anade un mensaje al archivo de log
	//! @param message Mensaje a anadir al log
	//! @return TRUE si el mensaje se ha anadido correctamente al log o FALSE en caso contrario
	static bool Frac3D_Log(const char* message, ...);

	//! @brief Anade un mensaje al archivo de log y tambien lo imprime en stderr
	//! @param message Mensaje a anadir al log
	//! @return TRUE si el mensaje se ha anadido correctamente al log o FALSE en caso contrario
	static bool Frac3D_ErrLog(const char* message, ...);

	//! @brief Anade al log una las capacidades de OpenGL
	//!
	//! Anade al log las capacidadades de OpenGL disponibles segun nuestro hardware grafico
	static void Fra3D_GLParams();
};

#endif