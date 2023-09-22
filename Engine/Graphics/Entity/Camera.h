#pragma once

#include <glm/glm.hpp>
#include "../vendors/glad/glad.h"
#include "../Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Input.h"
#include "../Transform.h"

class Camera
{

public:
	Camera() = default;
	Camera(glm::vec3 position);

	void Projection();
	void SetSpeed(GLfloat speed);
	void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);

	void MoveUp(GLfloat speed);
	void MoveDown(GLfloat speed);
	void MoveLeft(GLfloat speed);
	void MoveRight(GLfloat speed);
	void MoveForward(GLfloat speed);
	void MoveBackward(GLfloat speed);

	void Update(){}
	void SendToShader(const Shader& shader);
	void SetFov(GLfloat fov);

private:
	GLfloat m_speed;
	GLfloat m_fov;

	Transform m_transform;

	glm::mat4 m_view;
	glm::mat4 m_proj;

	glm::vec3 m_direction;
	glm::vec3 m_up;


};