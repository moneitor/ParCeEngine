#include "AssMesh.h"

assMesh::assMesh( std::vector<assVertex> vertices, std::vector<GLuint> indices)
:m_vertices{vertices},
 m_indices{indices}
{
}

assMesh::~assMesh()
{
}
