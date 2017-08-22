#ifndef FE_ConvertTypes_H
#define FE_ConvertTypes_H

#include <iostream>
#include <string>
#include <sstream>	// conversion entre std::string y tipos primitivos
#include <fstream>

//! @class FE_ConvertTypes clase de utilidad para la conversion de tipos
class FE_ConvertTypes
{
public:
	//! @brief Convierte un tipo primitivo a cadena
	//! @param T tipo primitivo (int, float, ...)
	//! @return Tipo convertido a cadena
	template <typename T>
	static std::string toString(T const &val)
	{
		std::ostringstream ostr;
		ostr << val;

		return ostr.str();
	}

	//! @brief Convierte una cadena a tipo primitivo
	//! @param val cadena
	//! @return cadena convertida a tipo
	template <typename T>
	static T toType(std::string const &val)
	{
		std::istringstream istr(val);
		T returnVal;
		if (!(istr >> returnVal))
		{
			std::cout << "Fracture Init Config Parser ERROR: No se ha recibido un " + (std::string)typeid(T).name() + " valido!\n";
			std::cin.ignore();
			std::cin.get();

			exit(EXIT_FAILURE);
		}

		return returnVal;
	}

	//! @brief Convierte una cadena a cadena (funcion de conversion especializada)
	//! @param val cadena
	//! @return cadena convertida
	//
	// Esta funcion es auxiliar a toString debido a que si pasamos como valor la cadena "valor valor"
	// la funcion istringstream parara de extraer cuando encuentre el primer espacio. De esta forma
	// evitamos que esto ocurra
	template <>
	static std::string toType(std::string const &val)
	{
		return val;
	}
};
#endif