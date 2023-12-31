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

// struct assFace
// {
//     std::vector<glm::vec3> vertices;
// };


class assMesh 
{
public:
    assMesh(std::vector<assVertex> vertices, std::vector<GLuint> indices);
    ~assMesh();
    std::vector<GLuint> Get_Indices()
    {
        return this->m_indices;
    }

    std::vector<assVertex> Get_Vertices()
    {
        return this->m_vertices;
    }

    std::vector<glm::vec3> Get_Normals()
    {
        return this->m_normals;
    }

    std::vector<glm::vec4> Get_Colors()
    {
        return this->m_colors;
    }

protected:
    std::vector<assVertex> m_vertices;
    std::vector<GLuint>    m_indices;
    std::vector<glm::vec3> m_normals;    
    std::vector<glm::vec4> m_colors;    
};
