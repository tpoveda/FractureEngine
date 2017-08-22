#ifndef FEC_Transform_H
#define FEC_Transform_H

#include "glm.hpp"
#include <gtx/quaternion.hpp>
#include "../Interfaces/FE_Component.h"

class FEC_Transform : public FE_Component
{
public:
	FEC_Transform();
	virtual ~FEC_Transform();

	virtual void update();

	virtual void setRotation(const glm::quat& quat);
	void setRotation(const glm::mat4& mat);
	void setRotation(float angle, const glm::vec3& axis);
	void rotate(const glm::quat& quat);
	void rotate(float angle, const glm::vec3& axis);

	virtual void setTranslation(const glm::vec3& translation);
	void setTranslation(float x, float y, float z);
	void translate(const glm::vec3& translation);
	void translate(float x, float y, float z);

	void setScale(const glm::vec3& scale);
	void setScale(float scale);
	void scale(const glm::vec3& scaleAmount);
	void scale(float amountScale);

	void applyTransform(const FEC_Transform& transform);

	glm::vec3 getRightVector();
	glm::vec3 getUpVector();
	glm::vec3 getForwardVector();

	glm::mat4 getMatrix();
	void setMatrix(glm::mat4 matrixs);

private:
	glm::mat4 m_matrix;
	glm::quat m_rotation;
	glm::vec3 m_translation;
	glm::vec3 m_scale;
};


#endif