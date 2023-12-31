#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Shader.h"
#include "../vendors/glad/glad.h"
#include "World.h"
#include "../Transform.h"
#include "../Buffer.h"


class EmptyObject
{
public:
    EmptyObject(World *parent = nullptr);
    virtual ~EmptyObject() = default;   

	virtual void SetColor(const glm::vec4 &color) = 0;
	const glm::vec4 GetColor();

    virtual void Update() = 0;
	virtual void Render(const Shader& shader, Buffer::DrawType drawType);

	bool IsTextured();
	void IsTextured(bool isTextured);

	Transform &GetTransform();	

    enum  ObjectType 
	{ 
		Quad,
		Cube, 
		Cylinder,
		Sphere,
		Geometry,
		PerspectiveGrid
	};

    virtual ObjectType GetObjectType() = 0;


protected:	
	glm::vec4 m_color;

	bool m_isTextured;

	World *m_parent;
	Transform m_transform;
	glm::mat3 m_normal;	
};