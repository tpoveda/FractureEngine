/////////////////////////////////////
////// Fracture Games
////// Frac3D Engine
////// Singleton.h
/////////////////////////////////////

#ifndef F3D_Singleton_H
#define F3D_Singleton_H

template<class T>

//! @class F3D_Singleton Clase que define el patron de diseno Singleton
//
// Este tipo de patron nos permite asegurar que en todo momento solamente existe una instancia de la clase creada
class F3D_Singleton
{
public:
	//! @brief Devuelve un puntero a la instancia de la clase
	//! @return Puntero a la instancia de la clase
	//
	// Si el objeto no existia (es la primera vez que se crea) se crea
	static T* getInstance()
	{
		if (!instance)
		{
			instance = new T();
		}
		return instance;
	}

	//! @brief Elimina la instancia de la clase
	static void terminate()
	{
		if (instance)
		{
			delete instance;

			instance = nullptr;
		}
		
	}

protected:
	F3D_Singleton() {}
	virtual ~F3D_Singleton() {}

private:
	static T* instance;
};

template<class T>
T* F3D_Singleton<T>::instance = nullptr;


#endif