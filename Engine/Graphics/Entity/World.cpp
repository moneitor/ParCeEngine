#include "World.h"
#include "World.h"



World::World()
    :m_position{glm::vec3(0.0f)}, 
    m_rotation{glm::vec3(0.0f)}, 
    m_transform{glm::mat4(1.0f)}
{
}
World::~World()
{
}

Transform &World::GetTransform()
{
    return m_transform;
}
