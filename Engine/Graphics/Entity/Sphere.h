#pragma once

#include <glm/glm.hpp>
#include "../vendors/glad/glad.h"
#include "../Buffer.h"
#include "../Shader.h"
#include "../Material.h"
#include "EmptyObject.h"
#include <vector>

#include "../Utilities/Utility.h"

#include <string>

class Sphere : public EmptyObject{

public:
	Sphere(World *parent = nullptr);
	~Sphere() override;

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
	GLuint lats;
	GLuint longs;
};