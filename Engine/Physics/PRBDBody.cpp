#include "PRBDBody.h"

pRBDBody::pRBDBody(pRBDShape *shape, float mass_)
:rbdShape{shape},
position{pVec3(0.0f, 0.0f, 0.0f)},
velocity{pVec3(0.0f)},
acceleration{pVec3(0.0f)},
netForce{pVec3(0.0f)},
elasticity{1.0f},
mass{mass_},
invMass{1.0f/mass_},
active{true}
{
    if (mass == 0)
    {
        invMass = 0;
    } 
    else
    {
        invMass = 1/mass;
    }
}

pRBDBody::pRBDBody(pRBDShape *shape, const pVec3 &pos, float mass_)
:rbdShape{shape},
position{pos},
velocity{pVec3(0.0f)},
acceleration{pVec3(0.0f)},
netForce{pVec3(0.0f)},
elasticity{1.0f},
mass{mass_},
invMass{1.0f/mass_},
active{true}
{
    if (mass == 0)
    {
        invMass = 0;
    } 
    else
    {
        invMass = 1/mass;
    }
}

pRBDBody::~pRBDBody()
{
    delete(rbdShape);
}

pRBDShape *pRBDBody::GetShape()
{
    return rbdShape;
}

pVec3 pRBDBody::Pos()
{
    return position;
}

void pRBDBody::SetPosition(const pVec3 &pos)
{
    this->position = pos;
}

void pRBDBody::SetPosition(float x, float y, float z)
{
    this->position = pVec3(x, y, z);
}

pVec3 pRBDBody::Vel()
{
    return velocity;
}

void pRBDBody::SetVelocity(const pVec3 &vel)
{
    this->velocity = vel;
}

void pRBDBody::SetVelocity(float x, float y, float z)
{
    this->velocity = pVec3(x, y, z);
}

pVec3 pRBDBody::Accel()
{
    return acceleration;
}

void pRBDBody::SetAcceleration(const pVec3 &accel)
{
    this->acceleration = accel;
}

void pRBDBody::SetAcceleration(float x, float y, float z)
{
    this->acceleration = pVec3(x, y, z);
}

float pRBDBody::Elasticity()
{
    return this->elasticity;
}

void pRBDBody::SetElasticity(float elasticity_)
{
    this->elasticity = elasticity_;
}

float pRBDBody::Mass()
{
    return this->mass;
}

void pRBDBody::AddForce(const pVec3 &force)
{
    this->netForce += force;
}

void pRBDBody::CleanForces()
{
    this->netForce = pVec3(0.0f);
}

void pRBDBody::SetActive(bool value)
{
    this->active = value;
}


pVec3 pRBDBody::WorldToLocal(const pVec3 &vec) 
{
    pVec3 tempVec = vec;
    pVec3 temp = tempVec - GetCenterOfMassWorldSpace();
    pQuat invOrient = rotation.Invert();
    pVec3 localSpace = invOrient.RotateVector(temp);

    return localSpace;
}

pVec3 pRBDBody::LocalToWorld(const pVec3 &vec) 
{
    pVec3 worldSpace = GetCenterOfMassWorldSpace() + rotation.RotateVector(vec);
    return worldSpace;
}

pVec3 pRBDBody::GetCenterOfMassWorldSpace() 
{
    const pVec3 centerOfMass = rbdShape->GetCenterOfMass();

    const pVec3 pos = position + (rotation.RotateVector(centerOfMass));
    return pos;
}

pVec3 pRBDBody::GetCenterOfMassLocalSpace() 
{
    const pVec3 com = rbdShape->GetCenterOfMass();
    return com;
}

void pRBDBody::Integrate(float dt)
{
    if(active)
    {
        this->acceleration = netForce / mass;
        this->velocity += acceleration * dt;
        this->position += Vel() * dt;
    }

    CleanForces();
}
