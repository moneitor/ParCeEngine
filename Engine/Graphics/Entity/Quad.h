#pragma once

#include <glm/glm.hpp>
#include "../vendors/glad/glad.h"
#include "../Buffer.h"
#include "../Texture.h"
#include "../Shader.h"
#include "../Material.h"
#include "EmptyObject.h"

class Quad : public EmptyObject{

public:

	Quad(World *parent = nullptr);
	~Quad() override;

	virtual void SetColor(const glm::vec4 &color) override;

	virtual void Update() override {};
	virtual void Render(const Shader& shader) override;

	ObjectType GetObjectType() override
	{
		return m_objType;
	}

private:

	

	Buffer m_buffer;	
	Texture m_texture;
	Material m_material;

	ObjectType m_objType;
};