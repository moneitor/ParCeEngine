#include "Transform.h"

Transform::Transform(const glm::mat4 &matrix)
    :m_matrix{glm::mat4(1.0f)},
    m_position{glm::vec3(0.0f)}, 
	m_rotation{glm::vec3(0.0f)}, 
	m_scale{glm::vec3(1.0f)},
    m_isDirty{true}
{
}

const glm::vec3 &Transform::GetPosition() const
{
    return m_position;
}

const glm::vec3 &Transform::GetRotation() const
{
    return m_rotation;
}

const glm::vec3 &Transform::GetScale() const
{
    return m_scale;
}

const glm::mat4 &Transform::GetMatrix()
{
    UpdateTransform();

    return m_matrix;
}

void Transform::SetIdentity()
{
    m_position = glm::vec3(0.0f);
    m_rotation = glm::vec3(0.0f);
    m_scale = glm::vec3(1.0f);

    UpdateTransform();
    m_isDirty = true;
}

void Transform::SetTransform(const glm::mat4 &tm)
{ 
    glm::vec3 position;  
    glm::vec3 scale;  
    glm::quat rotationQ;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(tm, scale, rotationQ, position, skew, perspective);

    glm::vec3 rotation = glm::eulerAngles(rotationQ);
    rotation = glm::vec3(glm::degrees(rotation.x), glm::degrees(rotation.y), glm::degrees(rotation.z));

    this->m_matrix = tm;

    SetPosition(position.x, position.y, position.z);
    SetScale(scale.x, scale.y, scale.z);
    SetRotation(rotation.x, rotation.y, rotation.z);


    std::cout << rotation.x << ", " << rotation.y << ", " << rotation.z << std::endl;

    m_isDirty = true;
}

void Transform::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->m_position.x = x;
	this->m_position.y = y;
	this->m_position.z = z;

    UpdateTransform();
    m_isDirty = true;
}

void Transform::SetPosition(GLfloat value)
{
    this->m_position.x = value;
	this->m_position.y = value;
	this->m_position.z = value;

    UpdateTransform();
    m_isDirty = true;
}

void Transform::SetRotation(GLfloat pitch, GLfloat yaw, GLfloat roll)
{
	this->m_rotation.x = pitch;
	this->m_rotation.y = yaw;
	this->m_rotation.z = roll;

    UpdateTransform();
    m_isDirty = true;
}

void Transform::SetScale(GLfloat x, GLfloat y, GLfloat z)
{
	this->m_scale.x = x;
	this->m_scale.y = y;
	this->m_scale.z = z;

    UpdateTransform();
    m_isDirty = true;
}

void Transform::SetScale(GLfloat value)
{
    this->m_scale.x = value;
	this->m_scale.y = value;
	this->m_scale.z = value;

    UpdateTransform();
    m_isDirty = true;
}


void Transform::UpdateTransform()
{
    if(m_isDirty)
    {   
        m_matrix = glm::mat4(1.0f);

        m_matrix = glm::translate(m_matrix, m_position);

        m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	    m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	    m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        m_matrix = glm::scale(m_matrix, m_scale);

        m_isDirty = false;
    }
}
