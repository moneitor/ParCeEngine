#include "PRBDShape.h"

pRBDShape::pRBDShape()
{
}

pRBDShape::~pRBDShape()
{
}

pShapeType pRBDShape::GetShapeType() const
{
    return pShapeType();
}





///////////// SPHERE ////////////////////////////

pRBDSphere::pRBDSphere(assModel *model, float radius_)
:m_radius{radius_}, m_model{model}, m_shapeType{pShapeType::SPHERE}, centerOfMass{pVec3(0.0f)}
{
    float mult = 2.0f/5.0f;
    float radius = GetRadius();
    float Inn = mult * radius * radius;
    m_inertiaTensorInv = pMat3(Inn,  0.0f, 0.0f,
                               0.0f, Inn,  0.0f,
                               0.0f, 0.0f, Inn);

    m_inertiaTensorInv = Inverse(m_inertiaTensorInv);


    this->GetMeshVertices();
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

pShapeType pRBDSphere::GetShapeType() const
{
    return m_shapeType;
}

void pRBDSphere::GetMeshVertices() 
{
    for(auto vertex: m_model->GetVertices() )
    {
        pVec3 tempVec = pVec3(vertex.x, vertex.y, vertex.z);
    }
}

pMat3 pRBDSphere::GetInertiaTensor() const
{
    return m_inertiaTensorInv;
}

pVec3 pRBDSphere::GetCenterOfMass() const
{
    return centerOfMass;
}




/////////////// CUBE ////////////////

pRBDCube::pRBDCube(assModel *model)
:m_model{model}, m_shapeType{pShapeType::CUBE}, centerOfMass{pVec3(0.0f)}
{
    this->GetMeshVertices();
}

pRBDCube::~pRBDCube()
{
}

assModel *pRBDCube::GetModel()
{
    return this->m_model;
}

pShapeType pRBDCube::GetShapeType() const
{
    return m_shapeType;
}

void pRBDCube::GetMeshVertices() 
{
    for(auto vertex: m_model->GetVertices() )
    {
        pVec3 tempVec = pVec3(vertex.x, vertex.y, vertex.z);
    }
}

pMat3 pRBDCube::GetInertiaTensor() const
{
    return m_inertiaTensorInv;
}

pVec3 pRBDCube::GetCenterOfMass() const
{
    return pVec3();
}

pRBDConvex::pRBDConvex(assModel *model)
{
}






/////////////// CONVEX ////////////////

pShapeType pRBDConvex::GetShapeType() const
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

void pRBDConvex::GetMeshVertices() 
{
    for(auto vertex: m_model->GetVertices() )
    {
        pVec3 tempVec = pVec3(vertex.x, vertex.y, vertex.z);
    }
}

pMat3 pRBDConvex::GetInertiaTensor() const
{
    return m_inertiaTensorInv;
}

pVec3 pRBDConvex::GetCenterOfMass() const
{
    return pVec3();
}
