#pragma once

#include <glm/glm.hpp>
#include "../Buffer.h"
#include "../Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Input.h"
#include "../Transform.h"

class Light
{

public:

	Light();
	~Light();

	void Update() {}
	void Render(const Shader& shader);
	void SendToShader(const Shader& shader);
	void SetSpeed(GLfloat speed);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void SetPosition(float x, float y, float z);
	
private:

	Buffer m_buffer;

	Transform m_transform;

	GLfloat m_speed;

	glm::mat4 m_model;
	
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

};