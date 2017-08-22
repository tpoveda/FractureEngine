#ifndef F3D_Time_H
#define F3D_Time_H

#include <time.h>
#include <chrono>
#include <thread>

//! @class F3D_Time Clase que permite conocer el tiempo de juego
class F3D_Time
{
public:
	//! @brief Devuelve el tiempo de juego
	//! @return El tiempo de juego
	static double GetTime();

	static double GetDelta();
	static void SetDelta(double value);

private:
	static double m_delta;
};

#endif 