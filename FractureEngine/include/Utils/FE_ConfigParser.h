/*********************************
Fracture Init Parser

*** FUNCIONAMIENTO BASICO Y CARACTERISTICAS ***
- Los parametros estan definidos con la estructura clave=valor
- Admite comentarios usando ; comentario
- Admite la forma clave = valor (con espacios entre el signo igual)
- Admite valores compuestos clave = valor valor
- No admite claves compuetas clave 1 = valor lo entiende como clave = valor
**********************************/

#ifndef FE_ConfigParser_H
#define FE_ConfigParser_H

#include <iostream>
#include <string>
#include <sstream>	// conversion entre std::string y tipos primitivos
#include <map>
#include <fstream>	// manejo de archivos
#include "FE_ConvertTypes.h"

class FE_ConfigParser
{
public:
	//! @brief Constructor de la clase FE_ConfigParser
	//! @param filename Nombre del archivo de configuracion a abrir
	FE_ConfigParser(const std::string& filename);

	//! @brief Funcion que comprueba que una clave dada no se encuentra ya dentro del mapa de parejas clave-valor
	//! @param key Clave a comprobar
	//! @return True si la clave ya existe en el mapa o False en caso contrario
	bool keyExists(const std::string& key) const;

	//! @brief Funcion que devuelve el valor de una clave especifica
	template <typename ValueType>
	ValueType getValueOfKey(const std::string &key, ValueType const &defaultValue = ValueType()) const
	{
		// si la clave no existe devolvemos el valor por defecto
		if (!keyExists(key))
		{
			return defaultValue;
		}

		return FE_ConvertTypes::toType<ValueType>(m_contents.find(key)->second);
	}


private:
	//! @brief Funcion que remueve un comentario de la linea
	//! @param line Linea de datos
	void removeComment(std::string& line) const;

	//! @brief Funcion que comprueba si existen espacios en blanco de la linea
	//! @param line Linea de datos
	//! @retun True si existen espacios en blanco en la linea o False en caso contrario
	//
	// El objetivo de esta funcion es usarla debido a que, por ejemplo, en el caso de una linea en la que
	// solo haya un comentario, al eliminarse, el resto de contendos sera solamente espacios en blanco. Ademas,
	// es una funcion const porque no altera ninguna funcion miembro de la clase
	bool checkWhiteSpaceLine(const std::string& line) const;
	
	//! @brief Funcion que verifica que la estructura de la linea (clave=valor) es correcta
	//! @param line Liena de datos con comentarios eliminados
	//! @return True si la estructura de la linea es correta o False en caso contrario
	bool validLine(const std::string& line) const;

	//! @brief Funcion que extrae la clave de la pareja clave=valor
	//! @param key Clave extraida (como referencia)
	//! @param sepPos Posicion del signo = en la linea
	//! @param line Linea de datos
	//
	// Esta funcion funciona correctamente si la estructura de la linea es correcta,
	// es decir, si es del tipo clave=valor. Para asegurar que esto es asi se usa
	// el metodo validLine
	void extractKey(std::string& key, size_t const &sepPos, const std::string& line) const;
	
	//! @brief Funcion que extrae el valor de la pareja clave=valor
	//! @param value Valor extraido (como referencia)
	//! @param sepPos Posicion del signo = en la linea
	//! @param line Linea de datos
	//
	// Esta funcion funciona correctamente si la estructura de la linea es correcta,
	// es decir, si es del tipo clave=valor. Para asegurar que esto es asi se usa
	// el metodo validLine
	void extractValue(std::string& value, size_t const &sepPos, const std::string& line) const;
	
	//! @brief Extra el contenido de la cadena y lo almacena en un mapa de claves-valor
	//! @param Linea de datos
	//
	// La pareja clave-valor extraido solo se almacenara en el mapa si pasa las comprobaciones
	// pertinentes, asegurando que la estructura de la pareja  clave-valor es correcta
	void extractContents(const std::string& line);

	//! @brief Funcion que parsea la linea
	//! @param linea Linea de datos, con los comentarios eliminados
	//! @param lineNo Numero de la linea en el archivo
	void parseLine(const std::string& line, size_t const lineNo);

	//! @brief Funcion que abre el archivo de configuracion, extrae y parsea el contenido del mismo
	void extractKeys();

	//! @brief Mapa que almacena las parejas clave-valor
	std::map<std::string, std::string> m_contents;

	//! @brief Nombre del archivo de configuracion
	std::string m_filename;

};

#endif