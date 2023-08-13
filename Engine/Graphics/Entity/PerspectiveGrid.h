#pragma once

#include "../Texture.h"
#include "../Material.h"
#include <string>
#include "../Shader.h"
#include "../Buffer.h"
#include "../Input.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../vendors/glad/glad.h"
#include "../Transform.h"
#include <glm/glm.hpp>
#include "EmptyObject.h"
#include "World.h"

class PerspectiveGrid : public EmptyObject
{
public:

	PerspectiveGrid(World *parent = nullptr);
	~PerspectiveGrid() override;

	virtual void SetColor(const glm::vec4 &color) override;

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