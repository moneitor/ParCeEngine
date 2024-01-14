#include "PRBDShapeCube.h"






/////////////// CUBE ////////////////

pRBDCube::pRBDCube(assModel *model)
:m_model{model}, m_shapeType{pShapeType::CUBE}, m_centerOfMass{pVec3(0.0f)}
{
    this->SetMeshVertices();
    this->SetMeshFaces();
    this->SetBounds();


    for (int i = 0; i < m_vertices_world.size(); i++)
    {
        m_bounds.Extend(m_vertices_world[i]);
    }

    m_bound_points_local.clear();
    m_bound_points_local.push_back( pVec3( m_bounds.minsize.GetX(), m_bounds.minsize.GetY(), m_bounds.minsize.GetZ() ) );
	m_bound_points_local.push_back( pVec3( m_bounds.maxsize.GetX(), m_bounds.minsize.GetY(), m_bounds.minsize.GetZ() ) );
	m_bound_points_local.push_back( pVec3( m_bounds.minsize.GetX(), m_bounds.maxsize.GetY(), m_bounds.minsize.GetZ() ) );
	m_bound_points_local.push_back( pVec3( m_bounds.minsize.GetX(), m_bounds.minsize.GetY(), m_bounds.maxsize.GetZ() ) );

	m_bound_points_local.push_back( pVec3( m_bounds.maxsize.GetX(), m_bounds.maxsize.GetY(), m_bounds.maxsize.GetZ() ) );
	m_bound_points_local.push_back( pVec3( m_bounds.minsize.GetX(), m_bounds.maxsize.GetY(), m_bounds.maxsize.GetZ() ) );
	m_bound_points_local.push_back( pVec3( m_bounds.maxsize.GetX(), m_bounds.minsize.GetY(), m_bounds.maxsize.GetZ() ) );
	m_bound_points_local.push_back( pVec3( m_bounds.maxsize.GetX(), m_bounds.maxsize.GetY(), m_bounds.minsize.GetZ() ) );

    m_bound_points_world.clear();
    m_bound_points_world.push_back( pVec3( m_bounds.minsize.GetX(), m_bounds.minsize.GetY(), m_bounds.minsize.GetZ() ) );
	m_bound_points_world.push_back( pVec3( m_bounds.maxsize.GetX(), m_bounds.minsize.GetY(), m_bounds.minsize.GetZ() ) );
	m_bound_points_world.push_back( pVec3( m_bounds.minsize.GetX(), m_bounds.maxsize.GetY(), m_bounds.minsize.GetZ() ) );
	m_bound_points_world.push_back( pVec3( m_bounds.minsize.GetX(), m_bounds.minsize.GetY(), m_bounds.maxsize.GetZ() ) );

	m_bound_points_world.push_back( pVec3( m_bounds.maxsize.GetX(), m_bounds.maxsize.GetY(), m_bounds.maxsize.GetZ() ) );
	m_bound_points_world.push_back( pVec3( m_bounds.minsize.GetX(), m_bounds.maxsize.GetY(), m_bounds.maxsize.GetZ() ) );
	m_bound_points_world.push_back( pVec3( m_bounds.maxsize.GetX(), m_bounds.minsize.GetY(), m_bounds.maxsize.GetZ() ) );
	m_bound_points_world.push_back( pVec3( m_bounds.maxsize.GetX(), m_bounds.maxsize.GetY(), m_bounds.minsize.GetZ() ) );

	m_centerOfMass = ( m_bounds.maxsize + m_bounds.minsize ) * 0.5f;




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
        m_vertices_world.push_back(tempVec);
    }    
}


std::vector<pVec3> pRBDCube::GetMeshVerticesLocal() const
{
    return m_vertices_local;
}

std::vector<pVec3> pRBDCube::GetMeshVerticesWorld() const
{
    return m_vertices_world;
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
    float dx = m_bounds.maxsize.GetX() - m_bounds.minsize.GetX();
    float dy = m_bounds.maxsize.GetY() - m_bounds.minsize.GetY();
    float dz = m_bounds.maxsize.GetZ() - m_bounds.minsize.GetZ();

    pMat3 tensor = pMat3();
    float xx, yy, zz;

    tensor.e11 = (dy * dy + dz * dz) / 12.0f;
    tensor.e22 = (dx * dx + dz * dz) / 12.0f;
    tensor.e33 = (dx * dx + dy * dy) / 12.0f;

    pVec3 center_of_mass;
    center_of_mass.SetX( (m_bounds.maxsize.GetX() + m_bounds.minsize.GetX()) * 0.5f );
    center_of_mass.SetY( (m_bounds.maxsize.GetY() + m_bounds.minsize.GetY()) * 0.5f );
    center_of_mass.SetZ( (m_bounds.maxsize.GetZ() + m_bounds.minsize.GetZ()) * 0.5f );

    pVec3 R = pVec3(0.0f, 0.0f, 0.0f) - center_of_mass;
    float RX = R.GetX();
    float RY = R.GetY();
    float RZ = R.GetZ();

    float R2 = R.MagnitudeSq();



    pVec3 row0 = pVec3(R2 - RX * RX,     RX * RY,            RX * RZ);
    pVec3 row1 = pVec3(RY * RX,          R2 - RY * RY,       RY * RZ);
    pVec3 row2 = pVec3(RZ * RX,          RZ * RY,            R2 - RZ * RZ);

    pMat3 modTensor = pMat3(row0, row1, row2);

    tensor = tensor + modTensor;

    return tensor;

}

pVec3 pRBDCube::GetCenterOfMass() const
{
    return m_centerOfMass;
}

void pRBDCube::UpdateVertices(const pQuat &orient, const pVec3 &pos)
{
    // TODO Update vertices with rotation and translation;
    std::vector<pVec3> vertices = GetMeshVerticesLocal();   

    pVec3 model_scale = m_model->GetTransform().GetScale();

    // Here we are updating the local vertices to world space so we can do collision operations with them
    for (int i = 0; i < vertices.size (); i++)
    {        
        pVec3 scaledVec = vertices[i] * model_scale[0];
        pVec3 rotatedVec = QVRotate(orient, scaledVec); // Rotate vertex by orient
        pVec3 translatedVec = rotatedVec + pos; // Offset vertex by rbd pos
        m_vertices_world[i] = translatedVec; // Populate world space vertices 
    }

    // Here we are updating the local space vertices of the bounds to world space, in case we need them for AABB operations
    pVec3 com = pVec3();
    for (int i = 0; i < m_bound_points_world.size (); i++)
    {
        pVec3 scaledVec = m_bound_points_local[i] * model_scale[0];
        pVec3 rotatedVec = QVRotate(orient, scaledVec); // Rotate vertex by orient
        pVec3 translatedVec = rotatedVec + pos; // Offset vertex by rbd pos
        m_bound_points_world[i] = translatedVec; // Populate world space vertices 
        com += translatedVec;
    }

    // this->m_centerOfMass = com / m_bound_points_world.size();

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

void pRBDCube::SetBounds()
{
    for (int i = 0; i < m_vertices_world.size(); i++)
    {
        m_bounds.Extend(m_vertices_world[i]);
    }
}

pBounds pRBDCube::GetBounds(const pVec3 &pos, const pQuat &orient) const
{
    pBounds tmp;
    for (int i = 0; i < m_vertices_local.size(); i++)
    {
        tmp.Extend(RotateVector(orient, m_vertices_local[i]) + pos);
    }
    return tmp;
}

pBounds pRBDCube::GetBounds() const
{
    pBounds tmp;
    for (int i = 0; i < m_vertices_world.size(); i++)
    {
        tmp.Extend(m_vertices_world[i]);
    }
    return tmp;
}

pVec3 pRBDCube::Support(const pVec3 &dir, const pVec3 &pos, const pQuat &orient, float bias) const
{
    pVec3 maxPt = RotateVector(orient, m_bound_points_local[0]) + pos;
    float maxdist = Dot(dir, maxPt);

    for (int i = 0; i <  m_bound_points_local.size(); i++)
    {
        pVec3 pt = RotateVector(orient, m_bound_points_local[i]) + pos;
        float dist = Dot(dir, pt);

        if (dist > maxdist)
        {
            maxdist = dist;
            maxPt = pt;
        }
    }

    pVec3 norm = dir.Normalize();
    norm *= bias;

    return maxPt + norm;
}


std::vector<pVec3> pRBDCube::GetBoundPoints() const
{
    return m_bound_points_world;
}

float pRBDCube::FastestLinearSpeed(const pVec3 &com, const pVec3 &angularVelocity, const pVec3 &dir)
{
    float maxSpeed = 0.0f;
    for (int i = 0; i < m_bound_points_local.size(); i++)
    {
        pVec3 r = m_bound_points_world[i] - com;
        pVec3 linearVelocity = Cross(angularVelocity, r);
        float speed = Dot(dir, linearVelocity);

        if (speed > maxSpeed)
        {
            maxSpeed = speed;
        }        
    }
    return maxSpeed ;
}
