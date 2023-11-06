
#include "Sphere.h"

void CreateSphere2(std::vector<GLfloat>& vertices, 
                   std::vector<GLuint>& indices,
                   float radius, 
                   unsigned int rings,
                   unsigned int sectors )
{
    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    int r, s;

    vertices.resize(rings * sectors * 3);
    // normals.resize(rings * sectors * 3);
    // texcoords.resize(rings * sectors * 2);
    std::vector<GLfloat>::iterator v = vertices.begin();
    // std::vector<GLfloat>::iterator n = normals.begin();
    // std::vector<GLfloat>::iterator t = texcoords.begin();
    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
            float const y = sin( -M_PI_2 + M_PI * r * R );
            float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
            float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

            // *t++ = s*S;
            // *t++ = r*R;

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;

            // *n++ = x;
            // *n++ = y;
            // *n++ = z;
    }

    indices.resize(rings * sectors * 4);
    std::vector<GLuint>::iterator i = indices.begin();
    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
    }
}



void CreateSphere(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, float radius, int slices, int stacks) {
    for (int stack = 0; stack <= stacks; ++stack) {
        float stackAngle = stack * M_PI / stacks;
        float stackRadius = radius * sin(stackAngle);
        float stackHeight = radius * cos(stackAngle);

        for (int slice = 0; slice <= slices; ++slice) {
            float sliceAngle = slice * 2 * M_PI / slices;
            float vertexX = stackRadius * cos(sliceAngle);
            float vertexY = stackRadius * sin(sliceAngle);
            float vertexZ = stackHeight;

            vertices.push_back(vertexX);
            vertices.push_back(vertexY);
            vertices.push_back(vertexZ);
        }
    }

    for (int stack = 0; stack < stacks; ++stack) {
        for (int slice = 0; slice < slices; ++slice) {
            int first = (stack * (slices + 1)) + slice;
            int second = first + slices + 1;
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
}

Sphere::Sphere(World *parent)	
	:EmptyObject(parent),
	m_objType{ObjectType::Sphere}
{	
	CreateSphere2(v_vertices, v_indices, 1, 100, 100);
	GLfloat *vertices = v_vertices.data();
	GLuint *indices = v_indices.data();
	// GLfloat *colors = v_colors.data();
	// GLfloat *normals = v_normals.data();

    for(auto i: v_indices)
    {
        std::cout << i << " ,";
    } std::cout << std::endl;

    std::cout << "Amount of vertices: " << v_vertices.size() << std::endl;
    std::cout << "Amount of indices: " << v_indices.size() << std::endl;
    std::cout << sizeof(vertices) << std::endl;

	m_buffer.CreateBuffer(v_vertices.size() + 1, true);

	m_buffer.FillEBO(indices, sizeof(indices), Buffer::FillType::Once);
	m_buffer.FillVBO(Buffer::VBOType::VertexBuffer, vertices, sizeof(vertices), Buffer::FillType::Once);

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

	for(size_t i = 0 ; i < 24; i++)
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
	// m_buffer.LinkVBO(shader, "colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGBA, Buffer::DataType::FloatData);
	// m_buffer.LinkVBO(shader, "normalIn", Buffer::VBOType::NormalBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);


	m_buffer.Render(Buffer::DrawType::Triangles);
}


