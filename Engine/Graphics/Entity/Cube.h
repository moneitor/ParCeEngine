#pragma once

#include <glm/glm.hpp>
#include "../Buffer.h"
#include "../Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Input.h"
#include "../Material.h"
#include "EmptyObject.h"

class Cube : public EmptyObject
{
public:

	Cube(World *parent = nullptr);
	~Cube() override;

	void SetColor(const glm::vec4 &color) override;

	virtual void Update() override {};
	virtual void Render(const Shader& shader) override;	

	ObjectType GetObjectType() override
	{
		return m_objType;
	}

private:
	Buffer m_buffer;
	Material m_material;

	ObjectType m_objType;
};