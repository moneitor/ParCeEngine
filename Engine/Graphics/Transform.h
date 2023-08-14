#pragma once

#include <iostream>
#include "../vendors/glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
 

class Transform
{
public:
    Transform(const glm::mat4 &matrix=glm::mat4(1.0f));

    const glm::vec3 &GetPosition() const;
    const glm::vec3 &GetRotation() const;
    const glm::vec3 &GetScale() const;
    const glm::mat4 &GetMatrix();

    void SetIdentity();
    void SetTransform(const glm::mat4 &tm);

    void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetRotation(GLfloat pitch, GLfloat yaw, GLfloat roll);
	void SetScale(GLfloat x, GLfloat y, GLfloat z);

    void UpdateTransform();

protected:
    bool m_isDirty;

    glm::mat4 m_matrix;

    glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

};