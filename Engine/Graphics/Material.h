#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "../vendors/glad/glad.h"
#include "Shader.h"
#include "Texture.h"
#include "Utilities/Utility.h"  //Graphics/Utilities/Utility.h


class Material
{

public:

	Material();

	const std::string& GetName() const;

	bool IsTextured() const;

	const Texture& GetNormalMap() const;
	const Texture& GetAmbientMap() const;
	const Texture& GetDiffuseMap() const;
	const Texture& GetSpecularMap() const;

	void SetShininess(GLfloat shininess);
	void SetAmbient(const glm::vec3& ambient);
	void SetDiffuse(const glm::vec3& diffuse);
	void SetSpecular(const glm::vec3& specular);
	
	void SendToShader(const Shader& shader) const;

private:

	std::string m_name;

	Texture m_normalMap;
	Texture m_ambientMap;
	Texture m_diffuseMap;
	Texture m_specularMap;

	GLfloat m_shininess;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

};
