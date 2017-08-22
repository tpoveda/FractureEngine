#include "../../../../include/Systems/Frac3DEngine/Layer0/F3D_Color.h"

const F3D_Color F3D_Color::WHITE = F3D_Color(1.0f, 1.0f, 1.0f, 1.0f);
const F3D_Color F3D_Color::BLACK = F3D_Color(0.0f, 0.0f, 0.0f, 1.0f);
const F3D_Color F3D_Color::RED = F3D_Color(1.0f, 0.0f, 0.0f, 1.0f);
const F3D_Color F3D_Color::GREEN = F3D_Color(0.0f, 1.0f, 0.0f, 1.0f);
const F3D_Color F3D_Color::BLUE = F3D_Color(0.0f, 0.0f, 1.0f, 1.0f);
const F3D_Color F3D_Color::YELLOW = F3D_Color(1.0f, 1.0f, 0.0f, 1.0f);
const F3D_Color F3D_Color::MAGENTA = F3D_Color(1.0f, 0.0f, 1.0f, 1.0f);
const F3D_Color F3D_Color::CYAN = F3D_Color(0.0f, 1.0f, 1.0f, 1.0f);
const F3D_Color F3D_Color::GREY = F3D_Color(0.5f, 0.5f, 0.5f, 1.0f);
const F3D_Color F3D_Color::BRIGHT_GREY = F3D_Color(0.75f, 0.75f, 0.75, 1.0f);
const F3D_Color F3D_Color::DARK_GREY = F3D_Color(0.25f, 0.25f, 0.25f, 1.0f);

const F3D_Color F3D_Color::DEFAULT_EMISSIVE = F3D_Color(0.0f, 0.0f, 0.0f, 1.0f);
const F3D_Color F3D_Color::DEFAULT_AMBIENT = F3D_Color(0.2f, 0.2f, 0.2f, 1.0f);
const F3D_Color F3D_Color::DEFAULT_DIFFUSE = F3D_Color(0.8f, 0.8f, 0.8f, 1.0f);
const F3D_Color F3D_Color::DEFAULT_SPECULAR = F3D_Color(0.0f, 0.0f, 0.0f, 1.0f);
const F3D_Color F3D_Color::DEFAULT_REFLECTION = F3D_Color(0.0f, 0.0f, 0.0f, 1.0f);
const F3D_Color F3D_Color::DEFAULT_REFRACTION = F3D_Color(0.0f, 0.0f, 0.0f, 1.0f);

F3D_Color::F3D_Color()
{
	m_rgba[0] = 0.0f;
	m_rgba[1] = 0.0f;
	m_rgba[2] = 0.0f;
	m_rgba[3] = 1.0f;
}

F3D_Color::F3D_Color(float luminance)
{
	m_rgba[0] = luminance;
	m_rgba[1] = luminance;
	m_rgba[2] = luminance;
	m_rgba[3] = 1.0f;
}

F3D_Color::F3D_Color(float r, float g, float b)
{
	m_rgba[0] = r;
	m_rgba[1] = g;
	m_rgba[2] = b;
	m_rgba[3] = 1.0f;
}

F3D_Color::F3D_Color(float r, float g, float b, float a)
{
	m_rgba[0] = r;
	m_rgba[1] = g;
	m_rgba[2] = b;
	m_rgba[3] = a;
}

F3D_Color::F3D_Color(const float rgba[4])
{
	m_rgba[0] = m_rgba[0];
	m_rgba[1] = m_rgba[1];
	m_rgba[2] = m_rgba[2];
	m_rgba[3] = m_rgba[3];
}

F3D_Color::F3D_Color(const F3D_Color& color)
{
	m_rgba[0] = color.m_rgba[0];
	m_rgba[1] = color.m_rgba[1];
	m_rgba[2] = color.m_rgba[2];
	m_rgba[3] = color.m_rgba[3];
}

F3D_Color::~F3D_Color()
{
}

void F3D_Color::setLuminance(float luminance)
{
	m_rgba[0] = luminance;
	m_rgba[1] = luminance;
	m_rgba[2] = luminance;
	m_rgba[3] = 1.0f;
}

void F3D_Color::setRGBA(float r, float g, float b, float a)
{
	m_rgba[0] = r;
	m_rgba[1] = g;
	m_rgba[2] = b;
	m_rgba[3] = a;
}

void F3D_Color::setRGBA(const float rgba[4])
{
	m_rgba[0] = m_rgba[0];
	m_rgba[1] = m_rgba[1];
	m_rgba[2] = m_rgba[2];
	m_rgba[3] = m_rgba[3];
}

void F3D_Color::setRGBA(float value, int index)
{
	m_rgba[index] = value;
}

void F3D_Color::setR(float r)
{
	m_rgba[0] = m_rgba[0];
}

void F3D_Color::setG(float g)
{
	m_rgba[1] = m_rgba[1];
}

void F3D_Color::setB(float b)
{
	m_rgba[2] = m_rgba[2];
}

void F3D_Color::setA(float a)
{
	m_rgba[3] = m_rgba[3];
}

const float* F3D_Color::getRGBA() const
{
	return m_rgba;
}

float F3D_Color::getRGBA(int index) const
{
	return m_rgba[index];
}

float F3D_Color::getR() const
{
	return m_rgba[0];
}

float F3D_Color::getG() const
{
	return m_rgba[1];
}

float F3D_Color::getB() const
{
	return m_rgba[2];
}

float F3D_Color::getA() const
{
	return m_rgba[3];
}