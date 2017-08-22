#ifndef F3D_Color_H
#define F3D_Color_H

//! @class F3D_Color Clase para definir colores
class F3D_Color
{
public:
	//! @brief Color por defecto blanco
	const static F3D_Color WHITE;
	//! @brief Color por defecto negro
	const static F3D_Color BLACK;
	//! @brief Color por defecto rojo
	const static F3D_Color RED;
	//! @brief Color por defecto verde
	const static F3D_Color GREEN;
	//! @brief Color por defecto azul
	const static F3D_Color BLUE;
	//! @brief Color por defecto amarillo
	const static F3D_Color YELLOW;
	//! @brief Color por defecto magenta
	const static F3D_Color MAGENTA;
	//! @brief Color por defecto cyan
	const static F3D_Color CYAN;
	//! @brief Color por defecto gris
	const static F3D_Color GREY;
	//! @brief Color por defecto gris claro
	const static F3D_Color BRIGHT_GREY;
	//! @brief Color por defecto gris oscuro
	const static F3D_Color DARK_GREY;
	
	//! @brief Color por defecto emisivo
	const static F3D_Color DEFAULT_EMISSIVE;
	//! @brief Color por defecto ambiente
	const static F3D_Color DEFAULT_AMBIENT;
	//! @brief Color por defecto difuso
	const static F3D_Color DEFAULT_DIFFUSE;
	//! @brief Color por defecto especular
	const static F3D_Color DEFAULT_SPECULAR;
	//! @brief Color por defecto reflexion
	const static F3D_Color DEFAULT_REFLECTION;
	//! @brief Color por defecto refraccion
	const static F3D_Color DEFAULT_REFRACTION;

	//! @brief Constructor del color
	F3D_Color();

	//! @brief Constructor del color
	//! @param luminance luminancia del color
	F3D_Color(float luminance);

	//! @brief Constructor del color
	//! @param r color canal rojo
	//! @param g color canal verde
	//! @param b color canal azul
	F3D_Color(float r, float g, float b);

	//! @brief Constructor del color
	//! @param r color canal rojo
	//! @param g color canal verde
	//! @param b color canal azul
	//! @param a color canal alpha
	F3D_Color(float r, float g, float b, float a);

	//! @brief Constructor del color
	//! @param rgba Matriz de colores
	F3D_Color(const float rgba[4]);

	//! @brief Constructor del color
	//! @param color color
	F3D_Color(const F3D_Color& color);

	//! @brief Destructor del color
	~F3D_Color();

	//! @brief Fija la luminancia del color
	//! @param luminance Luminancia del color
	void setLuminance(float luminance);

	//! @brief Fija el color de los canales
	//! @param r color canal rojo
	//! @param g color canal verde
	//! @param b color canal azul
	//! @param a color canal alpha
	void setRGBA(float r, float g, float b, float a);

	//! @brief Fija el color de los canales
	//! @param rgba Matriz de colores
	void setRGBA(const float rgba[4]);

	//! @brief Fija el color de los canales
	//! @param value Color del canal
	//! @param index Indice del canal (0 = rojo, 1 = verde, 2 = azul, 3 = transparencia)
	void setRGBA(float value, int index);

	//! @brief Fija el color del canal rojo
	//! @param r color del canal rojo
	void setR(float r);

	//! @brief Fija el color del canal verde
	//! @param g color del canal verde
	void setG(float g);

	//! @brief Fija el color del canal azul
	//! @param b color del canal azul
	void setB(float b);

	//! @brief Fija el color del canal alpha
	//! @param a color del canal alpha
	void setA(float a);

	//! @brief Devuelve el color
	//! @return color RGBA
	const float* getRGBA() const;

	//! @brief Devuelve el color del canal
	//! @param Indice del canal (0 = rojo, 1 = verde, 2 = azul, 3 = transparencia)
	//! @return color RGBA
	float getRGBA(int index) const;

	//! @brief Devuelve el color del canal rojo
	//! @return color del canal rojo
	float getR() const;

	//! @brief Devuelve el color del canal verde
	//! @return color del canal verde
	float getG() const;

	//! @brief Devuelve el color del canal azul
	//! @return color del canal azul
	float getB() const;

	//! @brief Devuelve el color del canal alpha
	//! @return color del canal alpha
	float getA() const;

private:
	//! @brief Colores
	float m_rgba[4];
};

#endif