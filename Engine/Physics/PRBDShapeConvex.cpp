#include "PRBDShapeConvex.h"


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

std::vector<pVec3> pRBDConvex::GetMeshVerticesWorld() const
{
    return m_vertices_world;
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
        m_vertices_world[i] = translatedVec; // Populate world space vertices 

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
