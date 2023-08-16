#include "AssMesh.h"

assMesh::assMesh(std::vector<assVertex> vertices, std::vector<GLuint> indices)
:m_vertices{vertices}, m_indices{indices}
{
    setupMesh();
    // FillBuffer();
}

assMesh::~assMesh()
{
    m_buffer.DestroyBuffer();
}

void assMesh::FillBuffer()
{
    m_buffer.CreateBuffer(m_indices.size(), true);
    m_buffer.FillEBO(&m_indices[0], sizeof(m_indices), Buffer::FillType::Once);

    m_buffer.FillVBO(Buffer::VBOType::VertexBuffer, &m_vertices[0], 
                                    m_vertices.size() * sizeof(glm::vec3), Buffer::FillType::Once);

    m_buffer.FillVBO(Buffer::VBOType::NormalBuffer, &m_normals[0], 
                                    m_normals.size() * sizeof(glm::vec3), Buffer::FillType::Once);

            
    for(const auto &vertex: m_vertices)
    {
        glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
        m_colors.push_back(color);
    }

    m_buffer.FillVBO(Buffer::VBOType::ColorBuffer, &m_colors[0], 
                                    m_colors.size() * sizeof(glm::vec4), Buffer::FillType::Once);

    m_buffer.LinkEBO();   
    
}

void assMesh::setupMesh()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_vertexVBO);
    glGenBuffers(1, &m_normalsVBO);
    glGenBuffers(1, &m_colorsVBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(assVertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(assVertex), (void*)0);

    // Vertex normals;
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(assVertex), (void*)offsetof(assVertex, Normal));
    // Vertex colors;

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(assVertex), (void*)offsetof(assVertex, Color));

    glBindVertexArray(0);

}

void assMesh::Render(const Shader &shader)
{        
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    
	// m_buffer.LinkVBO(shader, "vertexIn", Buffer::VBOType::VertexBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);
	// m_buffer.LinkVBO(shader, "colorIn", Buffer::VBOType::ColorBuffer, Buffer::ComponentType::RGBA, Buffer::DataType::FloatData);
	// m_buffer.LinkVBO(shader, "normalIn", Buffer::VBOType::NormalBuffer, Buffer::ComponentType::XYZ, Buffer::DataType::FloatData);


	m_buffer.Render(Buffer::DrawType::Triangles);
}


