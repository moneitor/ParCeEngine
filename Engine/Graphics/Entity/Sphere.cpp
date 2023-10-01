#include <glm/gtc/matrix_transform.hpp>
#include "Sphere.h"
#include "../Shader.h"
#include "../Input.h"

Sphere::Sphere(World *parent) : 
EmptyObject(parent), lats{24}, longs{24}
{
	m_objType = ObjectType::Sphere;

	std::vector<GLfloat> v_vertices;
	std::vector<GLfloat> v_colors;
	std::vector<GLuint> v_indices;
	std::vector<GLfloat> v_normals;
	std::vector<GLfloat> v_uvs;

/*
	GLfloat vertices[] = {
   //top-north-east
       0.0,  1.0,  0.0,
       0.0,  0.0,  1.0,
       1.0,  0.0,  0.0,

      //top-north-west
       0.0,  1.0,  0.0,
      -1.0,  0.0,  0.0,
       0.0,  0.0,  1.0,

      //top-south-west
       0.0,  1.0,  0.0,
       0.0,  0.0, -1.0,
      -1.0,  0.0,  0.0,

      //top-south-east
       0.0,  1.0,  0.0,
       1.0,  0.0,  0.0,
       0.0,  0.0, -1.0,

      //bottom-north-east
       0.0, -1.0,  0.0,
       1.0,  0.0,  0.0,
       0.0,  0.0,  1.0,

      //bottom-north-west
       0.0, -1.0,  0.0,
       0.0,  0.0,  1.0,
      -1.0,  0.0,  0.0,

      //bottom-south-west
       0.0, -1.0,  0.0,
      -1.0,  0.0,  0.0,
       0.0,  0.0, -1.0,

      //bottom-south-east
       0.0, -1.0,  0.0,
       0.0,  0.0, -1.0,
       1.0,  0.0,  0.0

	};


 	GLuint indices[] = {
      // first triangle
      0, 1, 2,
      // second triangle
      3, 4, 5,
      // third triangle
      6, 7, 8,
      // fourth triangle
      9, 10, 11,
      // fifth triangle
      12, 13, 14,
      // sixth triangle
      15, 16, 17,
      // seventh triangle
      18, 19, 20,
      // eighth triangle
      21, 22, 23
  };

	GLfloat colors[] = {
       //top-north-east
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
      //top-north-west
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,

      //top-south-west
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,

      //top-south-east
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,

      //bottom-north-east
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,

      //bottom-north-west
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,

      //bottom-south-west
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,

      //bottom-south-east
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,  1.0f, 1.0f,
	};

	GLfloat normals[] = {
       //top-north-east
       0.0f, 1.0f,  0.0f,
       0.0f,  0.0f,  1.0f,
       1.0f,  0.0f,  0.0f,
      //top-north-west
       0.0f,  1.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
       0.0f,  0.0f,  1.0f,

      //top-south-west
       0.0f,  1.0f,  0.0f,
       0.0f,  0.0f, -1.0f,
      -1.0f,  0.0f,  0.0f,

      //top-south-east
       0.0f, -1.0f,  0.0f,
       1.0f,  0.0f,  0.0f,
       0.0f,  0.0f, -1.0f,

      //bottom-north-east
       0.0f, -1.0f,  0.0f,
       1.0f,  0.0f,  0.0f,
       0.0f,  0.0f,  1.0f,

      //bottom-north-west
       0.0f, -1.0f,  0.0f,
       0.0f,  0.0f,  1.0f,
      -1.0f,  0.0f,  0.0f,

      //bottom-south-west
       0.0f, -1.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
       0.0f,  0.0f, -1.0f,

      //bottom-south-east
       0.0f, 1.0f,  0.0f,
       0.0f,  0.0f, -1.0f,
       1.0f,  0.0f,  0.0f
	};

	GLfloat UVs[] = {
       //top-north-east
       0.0f, 1.0f,  0.0f,
       0.0f,  0.0f,  1.0f,
       1.0f,  0.0f,  0.0f,
      //top-north-west
       0.0f,  1.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
       0.0f,  0.0f,  1.0f,

      //top-south-west
       0.0f,  1.0f,  0.0f,
       0.0f,  0.0f, -1.0f,
      -1.0f,  0.0f,  0.0f,

      //top-south-east
       0.0f, -1.0f,  0.0f,
       1.0f,  0.0f,  0.0f,
       0.0f,  0.0f, -1.0f,

      //bottom-north-east
       0.0f, -1.0f,  0.0f,
       1.0f,  0.0f,  0.0f,
       0.0f,  0.0f,  1.0f,

      //bottom-north-west
       0.0f, -1.0f,  0.0f,
       0.0f,  0.0f,  1.0f,
      -1.0f,  0.0f,  0.0f,

      //bottom-south-west
       0.0f, -1.0f,  0.0f,
      -1.0f,  0.0f,  0.0f,
       0.0f,  0.0f, -1.0f,

      //bottom-south-east
       0.0f, 1.0f,  0.0f,
       0.0f,  0.0f, -1.0f,
       1.0f,  0.0f,  0.0f
	};
*/

	GLfloat vertices[lats*longs*3];
	GLuint indices[lats*longs];	
	
	int indicator = 0;
	for (int i = 0; i <= lats; i++)
	{
		GLfloat lat0 = glm::pi<GLfloat>() * (-0.5 + (GLfloat)(i-1) / lats);
		GLfloat z0 = sin(lat0);
		GLfloat zr0 = cos(lat0);

		GLfloat lat1 = glm::pi<GLfloat>() * (-0.5 + (GLfloat)i / lats);
		GLfloat z1 = sin(lat1);
		GLfloat zr1 = cos(lat1);

		for(int j = 0; j <= longs; j++)
		{
			GLfloat lng = 2 * glm::pi<GLfloat>() * (GLfloat)(j-1)/longs;
			GLfloat x = cos(lng);
			GLfloat y = sin(lng);

			int v = i * j;

			vertices[v] = (x * zr0);
			vertices[v++]=(y * zr0);
			vertices[v+2] = z0;
			
			v_normals.push_back(x * zr0);
			v_normals.push_back(y * zr0);
			v_normals.push_back(z0);
			

			indices[v] = indicator;
			indicator++;
		}
	}

	for (int n = 0; n < v_vertices.size(); n++)
	{
		v_uvs.push_back(1.0f);
	}


	// GLfloat *vertices = v_vertices.data();
	// GLuint *indices = v_indices.data();	
	GLfloat *colors = v_colors.data();
	GLfloat *normals = v_normals.data();
	



	Utility::AddMessage("Vertex: " + std::to_string(vertices[50])) ;

	m_buffer.CreateBuffer(v_vertices.size(), false);
	m_buffer.FillEBO(indices, sizeof(indices), Buffer::FillType::Once);
	m_buffer.FillVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), Buffer::FillType::Once);
	m_buffer.FillVBO(Buffer::VBOType::ColorBuffer, colors, sizeof(colors), Buffer::FillType::Once);
	m_buffer.FillVBO(Buffer::VBOType::NormalBuffer, normals, sizeof(normals), Buffer::FillType::Once);

	m_buffer.LinkEBO();
	
	m_material.SetShininess(80.0f);
	m_material.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
	m_material.SetDiffuse(glm::vec3(0.2f, 0.2f, 0.2f));
	m_material.SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

}

Sphere::~Sphere()
{
	m_buffer.DestroyBuffer();
}

void Sphere::SetColor(const glm::vec4 &color)
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

void Sphere::Render(const Shader& shader)
{
	EmptyObject::Render(shader);
	
	m_material.SendToShader(shader);

	m_buffer.LinkVBO(shader, "vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader, "colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGBA, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader, "normalIn", Buffer::VBOType::NormalBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);


	m_buffer.Render(Buffer::DrawType::Triangles);

}


