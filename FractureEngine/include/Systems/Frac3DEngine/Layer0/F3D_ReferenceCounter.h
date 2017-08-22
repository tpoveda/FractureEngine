#ifndef F3D_ReferenceCounter_H
#define F3D_ReferenceCounter_H

#include <assert.h>

//! Clase base para casi todos los objetos del motor Fracture Engine
/**
Esta clase proporciona un contador de referencias a traves de los metodos Grab() y Drop()
La mayoria de objetos del motor se derivan de esta clase.

Cuando creamos un objeto usando un metodo que comienza con create, el objeto se creara y la funcion
nos devolvera un puntero a ese objeto. Si no necesitamos mas el objeto, deberemos llamar al metodo
Drop(). Esto destruira el objeto a no ser que el objeto este usando el objeto y sus referencias
no llegen a 0.
**/
class F3D_ReferenceCounter
{
public:
	//! Constructor de la clase IFractureReferenceCounter
	F3D_ReferenceCounter() : m_referenceCounter(0)
	{
	}

	//! Destructor de la clase IFractureReferenceCounter
	virtual ~F3D_ReferenceCounter()
	{
	}

	//! Aumenta el contador de referencias del objeto en uno
	void Grab() const
	{
		++m_referenceCounter;
	}

	//! Disminuye el contador de referencias del objeto en uno
	bool Drop() const
	{
		//assert(m_referenceCounter <= 0);

		--m_referenceCounter;
		if (m_referenceCounter == 0)
		{
			delete this;
			return true;
		}

		return false;
	}

	//! Devuelve las referencias actuales al recurso
	virtual int getReferenceCount()
	{
		return m_referenceCounter;
	}

private:
	//! El contador de referencias. Es mutable para permitir la el contador de referncias en objetos constantes (const)
	mutable int m_referenceCounter;
};

#endif