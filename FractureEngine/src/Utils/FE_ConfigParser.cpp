#include "../../include/Utils/FE_ConfigParser.h"

FE_ConfigParser::FE_ConfigParser(const std::string& filename)
{
	m_filename = filename;
	extractKeys();
}

bool FE_ConfigParser::keyExists(const std::string& key) const
{
	return m_contents.find(key) != m_contents.end();
}

void FE_ConfigParser::removeComment(std::string& line) const
{
	// Comprueba si la linea tiene un punto y coma ...
	if (line.find(';') != line.npos)
	{
		// .. si es asi elimina todo el contenido a partir del punto y coma (incluyendo el punto y coma)
		line.erase(line.find(';'));
	}
}


bool FE_ConfigParser::checkWhiteSpaceLine(const std::string& line) const
{
	return(line.find_first_not_of(' ') == line.npos);
}

bool FE_ConfigParser::validLine(const std::string& line) const
{
	std::string temp = line;

	// elimina cada caracter desde la posicion 0 (inicio de la linea) que sea de tabulacion o espacio en blanco
	temp.erase(0, temp.find_first_not_of("\t "));

	// tras la eliminacion, si el primer caracter es = significa que no tenemos clave y por lo tanto la estructura no es correcta
	if (temp[0] == '=') return false;

	// a partir de la posicion del = y hasta el final de la linea, si encontramos un caracter que no sea espacio, entonces tenemos
	// una estructura clave=valor correcta
	for (size_t i = temp.find('=') + 1; i < temp.length(); i++)
	{
		if (temp[i] != ' ') return true;
	}

	// solo se llegara aqui si la estructura no es correcta
	return false;
}

void FE_ConfigParser::extractKey(std::string& key, size_t const& sepPos, const std::string& line) const
{
	// la clave sera la primera subcadena extraida a partir del signo =
	key = line.substr(0, sepPos);

	// comprobamos que no existen espacios en blanco ni tabulaciones
	if (key.find('\t') != line.npos || key.find(' ') != line.npos)
	{
		key.erase(key.find_first_of("\t "));
	}
}

void FE_ConfigParser::extractValue(std::string& value, size_t const& sepPos, const std::string& line) const
{
	// creamos una subcadena desde la posicion de = + 1 hasta el final de la linea
	value = line.substr(sepPos + 1);

	// eliminamos espacios en blanco
	value.erase(0, value.find_first_not_of("\t "));
	value.erase(value.find_last_not_of("\t ") + 1);
}

void FE_ConfigParser::extractContents(const std::string& line)
{
	std::string temp = line;

	// eliminamos espacios en blanco
	temp.erase(0, temp.find_first_not_of("\t"));

	// nos almacenamos la posicion del signo = en la cadena
	size_t sepPos = temp.find('=');

	std::string key;
	std::string value;

	// extraemos la clave y el valor
	extractKey(key, sepPos, temp);
	extractValue(value, sepPos, temp);

	// si la clave no existe en el mapa enetonces insertamos la pareja clave-valor ...
	if (!keyExists(key)) m_contents.insert(std::pair<std::string, std::string>(key, value));
	else
	{
		// ... en caso contrario, mostramos un error al insertar
		std::cout << "Fracture Init Config Parser ERROR: Solamente pueden exisitr nombres de claves unicos!\n";
		std::cin.ignore();
		std::cin.get();

		exit(EXIT_FAILURE);
	}
}

void FE_ConfigParser::parseLine(const std::string& line, size_t const lineNo)
{
	// si no encontramos un signo = en la linea indicamos un error ya que no se ha encontrado un separador
	if (line.find('=') == line.npos)
	{
		std::cout << "Fracture Init Config Parser ERROR: No se ha encontrada separador en la linea: " + FE_ConvertTypes::toString(lineNo) + "!\n";
		std::cin.ignore();
		std::cin.get();

		exit(EXIT_FAILURE);
	}

	// si la linea no es valida (no tiene la estructura correcta) indicamos el error
	if (!validLine(line))
	{
		std::cout << "Fracture Init Config Parser ERROR: Formato erroneo en la linea: " + FE_ConvertTypes::toString(lineNo) + "\n";
		std::cin.ignore();
		std::cin.get();

		exit(EXIT_FAILURE);
	}

	// extraemos el contenido de la linea
	extractContents(line);
}

void FE_ConfigParser::extractKeys()
{
	std::ifstream file;

	// comprobamos que el archivo existe y si es asi lo abrimos
	file.open(m_filename.c_str());
	if (!file)
	{
		std::cout << "Fracture Init Config Parser ERROR: El archivo " + m_filename + " no se ha podido encontrar!\n";
		std::cin.ignore();
		std::cin.get();

		exit(EXIT_FAILURE);
	}

	std::string line;
	size_t lineNo = 0;

	// extraemos lienas, hasta que lleguemos al final del documento (EOF) ...
	while (std::getline(file, line))
	{
		lineNo++;
		std::string temp = line;

		// ... si la linea esta vacia la saltamos ...
		if (temp.empty()) continue;
		// ... si la linea tiene espacios los eliminamos ...
		removeComment(temp);

		// ... si la linea tiene solamente espacios en blanco la saltamos ...
		if (checkWhiteSpaceLine(temp)) continue;

		// ... y si las comprobaciones son correctas, parseamos la linea
		parseLine(temp, lineNo);
	}

	// por ultimo cerramos el archivo
	file.close();
}