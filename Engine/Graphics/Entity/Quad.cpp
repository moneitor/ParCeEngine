#include <glm/gtc/matrix_transform.hpp>
#include "Quad.h"
#include "../Shader.h"
#include "../Input.h"

Quad::Quad(World *parent) : EmptyObject(parent)
{
	m_objType = ObjectType::Quad;
	//data that represents vertices for quad
	GLfloat vertices[] = { -0.5f,  0.5f, 0.0f,
						    0.5f,  0.5f, 0.0f,
						    0.5f, -0.5f, 0.0f,
					       -0.5f, -0.5f, 0.0f  };

	//data that represents colors for quad
	GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 1.0f,
					     0.0f, 0.0f, 1.0f, 1.0f,
					     0.0f, 1.0f, 0.0f, 1.0f,
					     0.0f, 1.0f, 1.0f, 1.0f  };

	//data that represents normals for quad
	GLfloat normals[] = { 0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f,
						  0.0f, 0.0f, 1.0f };

	//data that represents UV coordinates for quad
	GLfloat UVs[] = { 0.0f, 1.0f,
					  1.0f, 1.0f,
					  1.0f, 0.0f,
					  0.0f, 0.0f };

	//our index buffer to control the rendering
	GLuint indices[] = { 0, 1, 3,
					     3, 1, 2 };

	m_buffer.CreateBuffer(6, true);
	m_buffer.FillEBO(indices, sizeof(indices), Buffer::FillType::Once);
	m_buffer.FillVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), Buffer::FillType::Once);
	m_buffer.FillVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), Buffer::FillType::Once);
	m_buffer.FillVBO(Buffer::VBOType::TextureBuffer, UVs, sizeof(UVs), Buffer::FillType::Once);
	m_buffer.FillVBO(Buffer::VBOType::NormalBuffer, normals, sizeof(normals), Buffer::FillType::Once);

	m_buffer.LinkEBO();
	
	m_texture.Load("Textures/Crate_1.png");

	m_material.SetShininess(50.0f);
	m_material.SetAmbient(glm::vec3(0.4f, 0.4f, 0.4f));
	m_material.SetDiffuse(glm::vec3(0.1f, 0.7f, 0.2f));
	m_material.SetSpecular(glm::vec3(0.8f, 0.8f, 0.8f));

}

Quad::~Quad()
{
	m_buffer.DestroyBuffer();
}

void Quad::SetColor(const glm::vec4 &color)
{
	std::vector <glm::vec4> colors;

	for(size_t i = 0 ; i < 4; i++)
	{
		colors.push_back(color);
	}

	m_buffer.FillVBO(Buffer::VBOType::ColorBuffer, 
					colors.data(),
					colors.size() * sizeof(glm::vec4),
					Buffer::FillType::Ongoing);

	m_color = color;
}

void Quad::Render(const Shader& shader)
{
	EmptyObject::Render(shader);
	
	m_material.SendToShader(shader);

	m_buffer.LinkVBO(shader, "vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader, "colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGBA, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader, "textureIn", Buffer::VBOType::TextureBuffer, Buffer::ComponentType::UV, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader, "normalIn", Buffer::VBOType::NormalBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);

	m_texture.Bind();
	m_buffer.Render(Buffer::DrawType::Triangles);
	m_texture.Unbind();
}


