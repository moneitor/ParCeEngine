#include "PRBDShape.h"

pRBDShape::pRBDShape()
{
}

pRBDShape::~pRBDShape()
{
}

pShapeType pRBDShape::GetShapeType()
{
    return pShapeType();
}





pRBDSphere::pRBDSphere(assModel *model, float radius)
:m_radius{radius}, m_model{model}, m_shapeType{pShapeType::SPHERE}
{
}

pRBDSphere::~pRBDSphere()
{
    delete m_model;
}

assModel *pRBDSphere::GetModel()
{
    return this->m_model;
}

float pRBDSphere::GetRadius() const
{
    return this->m_radius;
}

pShapeType pRBDSphere::GetShapeType()
{
    return m_shapeType;
}

void pRBDSphere::ChunkMeshVertices() 
{
    for(auto vertex: m_model->GetVertices() )
    {
        pVec3 tempVec = pVec3(vertex.x, vertex.y, vertex.z);
    }
}




pRBDCube::pRBDCube(assModel *model)
{
}

pRBDCube::~pRBDCube()
{
}

assModel *pRBDCube::GetModel()
{
    return nullptr;
}

pShapeType pRBDCube::GetShapeType()
{
    return m_shapeType;
}

void pRBDCube::ChunkMeshVertices() 
{
    for(auto vertex: m_model->GetVertices() )
    {
        pVec3 tempVec = pVec3(vertex.x, vertex.y, vertex.z);
    }
}




pRBDConvex::pRBDConvex(assModel *model)
{
}

pShapeType pRBDConvex::GetShapeType()
{
    return m_shapeType;
}

assModel *pRBDConvex::GetModel()
{
    return nullptr;
}

pRBDConvex::~pRBDConvex()
{
}

void pRBDConvex::ChunkMeshVertices() 
{
    for(auto vertex: m_model->GetVertices() )
    {
        pVec3 tempVec = pVec3(vertex.x, vertex.y, vertex.z);
    }
}
