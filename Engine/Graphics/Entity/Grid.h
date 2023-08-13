#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <string>
#include "../Shader.h"
#include "../Buffer.h"
#include "../Input.h"
#include "../vendors/glad/glad.h"
#include "../Transform.h"
#include "EmptyObject.h"
#include "World.h"

class Grid 
{
public:
    Grid(World *parent = nullptr);
    ~Grid();

    Transform &GetTransform();

    void Update(){}
    void Render(const Shader &shader);

private:

    Buffer m_buffer;

    Transform m_transform;

    glm::mat4 m_model;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};