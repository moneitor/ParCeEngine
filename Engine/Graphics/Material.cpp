#include "Material.h"

Material::Material()
    :m_shininess{0.0f},
    m_ambient{glm::vec3(0.0f)},
    m_diffuse{glm::vec3(0.0f)},
    m_specular{glm::vec3(0.0f)}
{
}

const std::string& Material::GetName() const
{
	return m_name;
}


const Texture& Material::GetNormalMap() const
{
	return m_normalMap;
}

const Texture& Material::GetAmbientMap() const
{
	return m_ambientMap;
}

const Texture& Material::GetDiffuseMap() const
{
	return m_diffuseMap;
}

const Texture& Material::GetSpecularMap() const
{
	return m_specularMap;
}

void Material::SetShininess(GLfloat shininess)
{
	m_shininess = shininess;
}

void Material::SetAmbient(const glm::vec3& ambient)
{
	m_ambient.r = ambient.r;
	m_ambient.g = ambient.g;
	m_ambient.b = ambient.b;
}

void Material::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse.r = diffuse.r;
	m_diffuse.g = diffuse.g;
	m_diffuse.b = diffuse.b;
}

void Material::SetSpecular(const glm::vec3& specular)
{
	m_specular.r = specular.r;
	m_specular.g = specular.g;
	m_specular.b = specular.b;
}


void Material::SendToShader(const Shader& shader) const
{
	shader.SendUniformData("material.shininess", m_shininess);
	shader.SendUniformData("material.ambient", m_ambient.r, m_ambient.g, m_ambient.b);
	shader.SendUniformData("material.diffuse", m_diffuse.r, m_diffuse.g, m_diffuse.b);
	shader.SendUniformData("material.specular", m_specular.r, m_specular.g, m_specular.b);
}
