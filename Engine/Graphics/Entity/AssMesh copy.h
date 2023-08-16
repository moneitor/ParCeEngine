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
    glm::vec2 TexCoords;
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
    std::vector<GLuint> m_indices;

    assMesh(std::vector<assVertex> vertices, std::vector<GLuint> indices);
    void Render(Shader &shader);

protected:
    GLuint VAO, VBO, EBO;
    void setupMesh();
};
