#include "../../include/Components/FEC_Transform.h"

FEC_Transform::FEC_Transform() :
m_translation(0, 0, 0),
m_scale(1, 1, 1)
{
}

FEC_Transform::~FEC_Transform()
{
}

void FEC_Transform::update()
{
	m_matrix = glm::mat4_cast(m_rotation);
	m_matrix[3] = glm::vec4(m_translation, 1.0f);
	m_matrix[0][0] *= m_scale.x;
	m_matrix[1][1] *= m_scale.y;
	m_matrix[2][2] *= m_scale.z;
}

void FEC_Transform::setRotation(const glm::quat& quat)
{
	m_rotation = quat;
}

void FEC_Transform::setRotation(const glm::mat4& mat)
{
	setRotation(glm::quat_cast(mat));
}

void FEC_Transform::setRotation(float angle, const glm::vec3& axis)
{
	setRotation(glm::angleAxis(glm::radians(angle), axis));
}

void FEC_Transform::rotate(const glm::quat& quat)
{
	setRotation(quat * m_rotation);
}

void FEC_Transform::rotate(float angle, const glm::vec3& axis)
{
	rotate(glm::angleAxis(glm::radians(angle), glm::normalize(axis)));
}

void FEC_Transform::setTranslation(const glm::vec3& translation)
{
	m_translation = translation;
}

void FEC_Transform::setTranslation(float x, float y, float z)
{
	setTranslation(glm::vec3(x, y, z));
}

void FEC_Transform::translate(const glm::vec3& translation)
{
	setTranslation(m_translation + translation);
}

void FEC_Transform::translate(float x, float y, float z)
{
	translate(glm::vec3(x, y, z));
}

void FEC_Transform::setScale(const glm::vec3& scale)
{
	m_scale = scale;
}

void FEC_Transform::setScale(float scale)
{
	setScale(glm::vec3(scale));
}

void FEC_Transform::scale(const glm::vec3& scaleAmount)
{
	setScale(m_scale * scaleAmount);
}

void FEC_Transform::scale(float amountScale)
{
	scale(glm::vec3(amountScale));
}

void FEC_Transform::applyTransform(const FEC_Transform& transform)
{
	translate(transform.m_translation);
	scale(transform.m_scale);
	rotate(transform.m_rotation);
}

glm::vec3 FEC_Transform::getRightVector()
{
	glm::mat3 rotation = glm::mat3_cast(m_rotation);
	return rotation[0];
}

glm::vec3 FEC_Transform::getUpVector()
{
	glm::mat3 rotation = glm::mat3_cast(m_rotation);
	return rotation[1];
}

glm::vec3 FEC_Transform::getForwardVector()
{
	glm::mat3 rotation = glm::mat3_cast(m_rotation);
	return rotation[2];
}

glm::mat4 FEC_Transform::getMatrix()
{
	return m_matrix;
}

void FEC_Transform::setMatrix(glm::mat4 matrix)
{
	m_matrix = matrix;
}
