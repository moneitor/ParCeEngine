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

void pRBDSphere::UpdateVertices(const pQuat &orient, const pVec3 &pos)
{
    // TODO Update vertices with rotation and translation;
    std::vector<pVec3> vertices = GetMeshVerticesLocal();    
    
    // m_vertices_world.clear(); // Clean world vertex array so it has the latest state of the simulation
    for (int i = 0; i < vertices.size (); i++)
    {
        pVec3 model_scale = m_model->GetTransform().GetScale();
        pVec3 scaledVec = vertices[i] * model_scale[0];
        pVec3 rotatedVec = QVRotate(orient, scaledVec); // Rotate vertex by orient
        pVec3 translatedVec = rotatedVec + pos; // Offset vertex by rbd pos
        // m_vertices_world.push_back(translatedVec); // Populate world space vertices 
        m_vertices_world[i] = translatedVec; // Populate world space vertices 
        // Utility::AddMessage(m_vertices_world[i].ToString());   
    }
    // Utility::AddMessage("\n");  
}

void pRBDSphere::UpdateFaces(const pQuat &orient, const pVec3 &pos)
{
    std::vector< std::vector<pVec3> > faces = GetMeshFaces();
    int faceNumber = 0;
    for(auto &face: faces)
    {              
        Utility::AddMessage("Face Number: " + std::to_string(faceNumber));
        for(auto &vertex: face)
        {
            // Utility::AddMessage(vertex.ToString());
        }
        // Utility::AddMessage("\n");
        faceNumber ++;
    }
}

pBounds pRBDSphere::GetBounds(const pVec3 &pos, const pQuat &orient) const
{
    pBounds tmp;
    tmp.minsize = pVec3(-m_radius) + pos;
    tmp.maxsize = pVec3(m_radius) + pos;
    return tmp;
}

pBounds pRBDSphere::GetBounds() const
{
    pBounds tmp;
    tmp.minsize = pVec3(-m_radius);
    tmp.maxsize = pVec3(m_radius);
    return tmp;
}

pVec3 pRBDSphere::Support(const pVec3 &dir, const pVec3 &pos, const pQuat &orient, float bias) const
{
    pVec3 _dir = dir.Normalize();

    return (pos + _dir).Scale(m_radius + bias);
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
        m_vertices_local.push_back(tempVec);
        m_vertices_world.reserve(m_vertices_local.size());
    }    
}

std::vector<pVec3> pRBDSphere::GetMeshVerticesLocal() const
{
    return m_vertices_local;
}

void pRBDSphere::SetMeshFaces()
{
    // Utility::AddMessage("SetMeshFaces Sphere");
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
        m_vertices_local.push_back(tempVec);
        m_vertices_world.reserve(m_vertices_local.size());
    }    
}


std::vector<pVec3> pRBDCube::GetMeshVerticesLocal() const
{
    return m_vertices_local;
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

void pRBDCube::UpdateVertices(const pQuat &orient, const pVec3 &pos)
{
    // TODO Update vertices with rotation and translation;
    std::vector<pVec3> vertices = GetMeshVerticesLocal();    
    
    // m_vertices_world.clear(); // Clean world vertex array so it has the latest state of the simulation
    for (int i = 0; i < vertices.size (); i++)
    {
        pVec3 model_scale = m_model->GetTransform().GetScale();
        pVec3 scaledVec = vertices[i] * model_scale[0];
        pVec3 rotatedVec = QVRotate(orient, scaledVec); // Rotate vertex by orient
        pVec3 translatedVec = rotatedVec + pos; // Offset vertex by rbd pos
        // m_vertices_world.push_back(translatedVec); // Populate world space vertices 
        m_vertices_world[i] = translatedVec; // Populate world space vertices 
        // Utility::AddMessage(m_vertices_world[i].ToString());   
    }
    // Utility::AddMessage("\n");       
}

void pRBDCube::UpdateFaces(const pQuat &orient, const pVec3 &pos)
{
    std::vector< std::vector<pVec3> > faces = GetMeshFaces();
    int faceNumber = 0;
    for(auto &face: faces)
    {              
        // Utility::AddMessage("Face Number: " + std::to_string(faceNumber));
        for(auto &vertex: face)
        {
            // Utility::AddMessage(vertex.ToString());
        }
        // Utility::AddMessage("\n");
        faceNumber ++;
    }
}

pBounds pRBDCube::GetBounds(const pVec3 &pos, const pQuat &orient) const
{
    return pBounds();
}

pBounds pRBDCube::GetBounds() const
{
    return pBounds();
}

pVec3 pRBDCube::Support(const pVec3 &dir, const pVec3 &pos, const pQuat &orient, float bias) const
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
        m_vertices_local.push_back(tempVec);
        m_vertices_world.reserve(m_vertices_local.size());
    }    
}

std::vector<pVec3> pRBDConvex::GetMeshVerticesLocal() const
{
    return m_vertices_local;
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

void pRBDConvex::UpdateVertices(const pQuat &orient, const pVec3 &pos)
{
    // TODO Update vertices with rotation and translation;
    std::vector<pVec3> vertices = GetMeshVerticesLocal();    
    
    // m_vertices_world.clear(); // Clean world vertex array so it has the latest state of the simulation
    for (int i = 0; i < vertices.size (); i++)
    {
        pVec3 model_scale = m_model->GetTransform().GetScale();
        pVec3 scaledVec = vertices[i] * model_scale[0];
        pVec3 rotatedVec = QVRotate(orient, scaledVec); // Rotate vertex by orient
        pVec3 translatedVec = rotatedVec + pos; // Offset vertex by rbd pos
        // m_vertices_world.push_back(translatedVec); // Populate world space vertices 
        m_vertices_world[i] = translatedVec; // Populate world space vertices 
        Utility::AddMessage(m_vertices_world[i].ToString());   
    }
    // Utility::AddMessage("\n");  
}

void pRBDConvex::UpdateFaces(const pQuat &orient, const pVec3 &pos)
{
    std::vector< std::vector<pVec3> > faces = GetMeshFaces();
    int faceNumber = 0;
    for(auto &face: faces)
    {              
        Utility::AddMessage("Face Number: " + std::to_string(faceNumber));
        for(auto &vertex: face)
        {
            // Utility::AddMessage(vertex.ToString());
        }
        // Utility::AddMessage("\n");
        faceNumber ++;
    }
}

pBounds pRBDConvex::GetBounds(const pVec3 &pos, const pQuat &orient) const
{
    return pBounds();
}

pBounds pRBDConvex::GetBounds() const
{
    return pBounds();
}

pVec3 pRBDConvex::Support(const pVec3 &dir, const pVec3 &pos, const pQuat &orient, float bias) const
{
    return pVec3();
}
