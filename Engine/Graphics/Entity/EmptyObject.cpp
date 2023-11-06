#include "EmptyObject.h"

EmptyObject::EmptyObject(World *parent) 
    :m_normal{glm::mat3(1.0f)},
    m_isTextured{false},
    m_parent{parent},
    m_color{glm::vec4(1.0f)}
{
    // std::cout << "Empty object constructor called: " << std::endl;
}

const glm::vec4 EmptyObject::GetColor()
{
    return m_color;
}

void EmptyObject::Render(const Shader &shader)
{    
	m_normal = glm::inverse(glm::mat3(m_transform.GetMatrix()));

    if (m_parent)
    {
        // std::cout << "Has parent. " << std::endl;
        shader.SendUniformData("model", m_parent->GetTransform().GetMatrix() *  m_transform.GetMatrix());        
    } else 
    {
        std::cout << "Has NO parent. " << std::endl;
        shader.SendUniformData("model", m_transform.GetMatrix()); 
    }
    
	shader.SendUniformData("normal", m_normal);
}

bool EmptyObject::IsTextured()
{
    return m_isTextured;
}

void EmptyObject::IsTextured(bool isTextured)
{
    m_isTextured = isTextured;
}

Transform &EmptyObject::GetTransform()
{
    return m_transform;
}


