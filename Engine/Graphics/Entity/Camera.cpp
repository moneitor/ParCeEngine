
#include "Camera.h"


Camera::Camera()
	:m_view{glm::mat4(1.0f)}, 
	m_proj{glm::mat4(1.0f)},
	m_direction{glm::vec3(0.0f, 0.0f, -1.0f)},
	m_up{glm::vec3(0.0f, 1.0f, 0.0f)},
	m_speed{0.01f},
	m_fov{45.0f}
{
	m_transform.SetPosition(0.0f, 3.0f, 20.0f);
}

void Camera::Projection()
{
	GLfloat FOV = m_fov;
	GLfloat aspectRatio = 1280.0f / 720.0f;

	m_proj = glm::perspective(FOV, aspectRatio, 0.001f, 5000.0f);
}

void Camera::SendToShader(const Shader& shader)
{
	auto position = m_transform.GetPosition();
	m_view = glm::lookAt(position, position + m_direction, m_up);
	shader.SendUniformData("proj", m_proj);
	shader.SendUniformData("view", m_view);
	shader.SendUniformData("cameraPosition", 
							position.x, 
							position.y, 
							position.z);
}

void Camera::SetSpeed(GLfloat speed)
{
	this->m_speed = speed;
}

void Camera::SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
}

void Camera::MoveUp(GLfloat speed)
{
	auto position = m_transform.GetPosition();
	position.y += speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveDown(GLfloat speed)
{
	auto position = m_transform.GetPosition();
	position.y -= speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveRight(GLfloat speed)
{
	auto position = m_transform.GetPosition();
	position.x += speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveLeft(GLfloat speed)
{
	auto position = m_transform.GetPosition();
	position.x -= speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveForward(GLfloat speed)
{
	auto position = m_transform.GetPosition();
	position.z -= speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::MoveBackward(GLfloat speed)
{
	auto position = m_transform.GetPosition();
	position.z += speed;
	m_transform.SetPosition(position.x, position.y, position.z);
}

void Camera::SetFov(GLfloat fov)
{
	m_fov = fov;
}
