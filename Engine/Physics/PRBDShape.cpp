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


    this->SetMeshVertices();
    this->SetMeshFaces();
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

void pRBDSphere::SetMeshVertices() 
{
    for(auto vertex: m_model->GetVertices() )
    {
        pVec3 tempVec = pVec3(vertex.x, vertex.y, vertex.z);
        m_vertices.push_back(tempVec);
    }    
}

std::vector<pVec3> pRBDSphere::GetMeshVertices() const
{
    return m_vertices;
}

void pRBDSphere::SetMeshFaces()
{
    Utility::AddMessage("SetMeshFaces Sphere");
    std::vector<assFace> tempFaces = m_model->GetFaces();
    for (auto face: tempFaces)
    {
        // Remember that we are working with triangle faces only
        std::vector<pVec3> newVertices;
        pVec3 newVertex0;
        newVertex0.SetX(face.vertices[0].x);
        newVertex0.SetY(face.vertices[0].y);
        newVertex0.SetZ(face.vertices[0].z);
        newVertices.push_back(newVertex0);

        pVec3 newVertex1;
        newVertex1.SetX(face.vertices[1].x);
        newVertex1.SetY(face.vertices[1].y);
        newVertex1.SetZ(face.vertices[1].z);
        newVertices.push_back(newVertex1);

        pVec3 newVertex2;
        newVertex2.SetX(face.vertices[2].x);
        newVertex2.SetY(face.vertices[2].y);
        newVertex2.SetZ(face.vertices[2].z);
        newVertices.push_back(newVertex2);


        m_faces.push_back(newVertices);
    }
}

std::vector<std::vector<pVec3>> pRBDSphere::GetMeshFaces() const
{
    return m_faces;
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
    this->SetMeshVertices();
    this->SetMeshFaces();
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

void pRBDCube::SetMeshVertices() 
{
    for(auto vertex: m_model->GetVertices() )
    {
        pVec3 tempVec = pVec3(vertex.x, vertex.y, vertex.z);
        m_vertices.push_back(tempVec);
    }    
}


std::vector<pVec3> pRBDCube::GetMeshVertices() const
{
    return m_vertices;
}

void pRBDCube::SetMeshFaces()
{
    
    std::vector<assFace> tempFaces = m_model->GetFaces();
    for (auto face: tempFaces)
    {
        // Remember that we are working with triangle faces only
        std::vector<pVec3> newVertices;
        pVec3 newVertex0;
        newVertex0.SetX(face.vertices[0].x);
        newVertex0.SetY(face.vertices[0].y);
        newVertex0.SetZ(face.vertices[0].z);
        newVertices.push_back(newVertex0);

        pVec3 newVertex1;
        newVertex1.SetX(face.vertices[1].x);
        newVertex1.SetY(face.vertices[1].y);
        newVertex1.SetZ(face.vertices[1].z);
        newVertices.push_back(newVertex1);

        pVec3 newVertex2;
        newVertex2.SetX(face.vertices[2].x);
        newVertex2.SetY(face.vertices[2].y);
        newVertex2.SetZ(face.vertices[2].z);
        newVertices.push_back(newVertex2);

        m_faces.push_back(newVertices);

    }
}

std::vector<std::vector<pVec3>> pRBDCube::GetMeshFaces() const
{
    return m_faces;
}

pMat3 pRBDCube::GetInertiaTensor() const
{
    return m_inertiaTensorInv;
}

pVec3 pRBDCube::GetCenterOfMass() const
{
    return pVec3();
}







/////////////// CONVEX ////////////////
pRBDConvex::pRBDConvex(assModel *model)
{
    this->SetMeshVertices();
    this->SetMeshFaces();
}

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

void pRBDConvex::SetMeshVertices() 
{
    for(auto vertex: m_model->GetVertices() )
    {
        pVec3 tempVec = pVec3(vertex.x, vertex.y, vertex.z);
        m_vertices.push_back(tempVec);
    }    
}

std::vector<pVec3> pRBDConvex::GetMeshVertices() const
{
    return m_vertices;
}

void pRBDConvex::SetMeshFaces()
{
    std::vector<assFace> tempFaces = m_model->GetFaces();
    for (auto face: tempFaces)
    {
        // Remember that we are working with triangle faces only
        std::vector<pVec3> newVertices;
        pVec3 newVertex0;
        newVertex0.SetX(face.vertices[0].x);
        newVertex0.SetY(face.vertices[0].y);
        newVertex0.SetZ(face.vertices[0].z);
        newVertices.push_back(newVertex0);

        pVec3 newVertex1;
        newVertex1.SetX(face.vertices[1].x);
        newVertex1.SetY(face.vertices[1].y);
        newVertex1.SetZ(face.vertices[1].z);
        newVertices.push_back(newVertex1);

        pVec3 newVertex2;
        newVertex2.SetX(face.vertices[2].x);
        newVertex2.SetY(face.vertices[2].y);
        newVertex2.SetZ(face.vertices[2].z);
        newVertices.push_back(newVertex2);


        m_faces.push_back(newVertices);
    }
}

std::vector<std::vector<pVec3>> pRBDConvex::GetMeshFaces() const
{
    return m_faces;
}

pMat3 pRBDConvex::GetInertiaTensor() const
{
    return m_inertiaTensorInv;
}

pVec3 pRBDConvex::GetCenterOfMass() const
{
    return pVec3();
}
