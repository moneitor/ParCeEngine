#include "AssMesh.h"

assMesh::assMesh( std::vector<assVertex> vertices, std::vector<GLuint> indices)
:m_vertices{vertices}, m_indices{indices}
{
    // setupMesh();
    // FillBuffer();
}

assMesh::~assMesh()
{
    m_buffer.DestroyBuffer();
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
}


