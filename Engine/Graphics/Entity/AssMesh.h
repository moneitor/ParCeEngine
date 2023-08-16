#pragma once

#include <string>
#include <vector>
#include "../vendors/glad/glad.h"
#include "../Buffer.h"
#include "../Shader.h"
#include "../Material.h"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "../Utilities/Utility.h"
#include "../Input.h"
#include "EmptyObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Utilities/Utility.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


struct assVertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Color;
};

struct tempTexture
{
    unsigned int id;
    std::string type;
};


class assMesh 
{
public:
    std::vector<assVertex> m_vertices;
    std::vector<GLuint>    m_indices;
    std::vector<glm::vec3> m_normals;    
    std::vector<glm::vec4> m_colors;    
    Buffer m_buffer;

    assMesh(std::vector<assVertex> vertices, std::vector<GLuint> indices, World *parent = nullptr);
    ~assMesh();
    void Render(const Shader &shader);

protected:
    GLuint m_VAO;
    GLuint m_vertexVBO;
    GLuint m_normalsVBO;
    GLuint m_colorsVBO;
    GLuint m_EBO;    

    
    void setupMesh();

    void FillBuffer();
};
