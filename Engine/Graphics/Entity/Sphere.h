#pragma once

#include <glm/glm.hpp>
#include "../Buffer.h"
#include "../Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Input.h"
#include "../Material.h"
#include "EmptyObject.h"

class Sphere : public EmptyObject
{
public:

	Sphere(World *parent = nullptr);
	~Sphere() override;

	void SetColor(const glm::vec4 &color) override;

	virtual void Update() override {};
	virtual void Render(const Shader& shader, Buffer::DrawType drawType) override;	

	ObjectType GetObjectType() override
	{
		return m_objType;
	}

private:
	Buffer m_buffer;
	Material m_material;

	ObjectType m_objType;

	std::vector<GLfloat> v_vertices;
	std::vector<GLfloat> v_colors;
	std::vector<GLuint> v_indices;
	std::vector<GLfloat> v_normals;
	std::vector<GLfloat> v_uvs;
};