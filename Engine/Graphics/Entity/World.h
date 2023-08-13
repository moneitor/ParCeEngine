#pragma once

#include <string>
#include "../Shader.h"
#include "../Buffer.h"
#include "../Input.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../vendors/glad/glad.h"
#include "../Transform.h"
#include <glm/glm.hpp>

class World
{
public:
    World();
    ~World();

    Transform &GetTransform();

private:
    Transform m_transform;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};