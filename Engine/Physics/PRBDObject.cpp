#include "PRBDObject.h"

pRBDObject::pRBDObject()
    :elasticity{1},
    mass{1},
    position{pVec3(0.0f, 0.0f, 0.0f)},
    vel{pVec3{0.0f, 0.0f, 0.0f}},
    netForce{pVec3{0.0f, 0.0f, 0.0f}},
    acceleration{pVec3{0.0f, 0.0f, 0.0f}}

{
}

pRBDObject::pRBDObject(const pVec3 & pos)
    :elasticity{1},
    mass{1},
    position{pos},
    vel{pVec3{0.0f, 0.0f, 0.0f}},
    netForce{pVec3{0.0f, 0.0f, 0.0f}},
    acceleration{pVec3{0.0f, 0.0f, 0.0f}}
{
}

pRBDObject::pRBDObject(assModel * model)
    :object{model},
    elasticity{1},
    mass{1},
    position{pVec3(0.0f, 0.0f, 0.0f)},
    vel{pVec3{0.0f, 0.0f, 0.0f}},
    netForce{pVec3{0.0f, 0.0f, 0.0f}},
    acceleration{pVec3{0.0f, 0.0f, 0.0f}}
{
}

pRBDObject::pRBDObject(assModel * model, const pVec3 &pos)
    :position{pos}, 
    object{model},
    elasticity{1},
    mass{1},
    vel{pVec3{0.0f, 0.0f, 0.0f}},
    netForce{pVec3{0.0f, 0.0f, 0.0f}},
    acceleration{pVec3{0.0f, 0.0f, 0.0f}}
{
}

assModel * pRBDObject::GetObject()
{
    return object;
}

pVec3 pRBDObject::Pos()
{
    return position;
}

void pRBDObject::SetPosition(const pVec3 & pos)
{
    this->position = pos;
}

void pRBDObject::SetPosition(float x, float y, float z)
{
    this->position = pVec3(x, y, z);
}

pVec3 pRBDObject::Vel()
{
    return this->vel;
}

void pRBDObject::SetVelocity(const pVec3 & vel)
{
    this->vel = vel;
}

void pRBDObject::SetVelocity(float x, float y, float z)
{
    this->vel = pVec3(x, y, z);
}

pVec3 pRBDObject::Accel()
{
    return this->acceleration;
}

void pRBDObject::SetAcceleration(const pVec3 & accel)
{
    this->acceleration = accel;
}

void pRBDObject::SetAcceleration(float x, float y, float z)
{
    this->acceleration = pVec3(x, y, z);
}

void pRBDObject::SetElasticity(float elasticity_)
{
    this->elasticity = elasticity_;
}

void pRBDObject::Integrate(float dt)
{
    // this->velocity += acceleration * dt;
    // this->position += velocity * dt;
    this->acceleration = netForce / mass;
    this->vel += acceleration * dt;
    this->position += Vel() * dt;

    CleanForces();
}

float pRBDObject::Elasticity()
{
    return this->elasticity;
}

void pRBDObject::AddForce(const pVec3 & force)
{
    this->netForce += force;
}

void pRBDObject::CleanForces()
{
    this->netForce = pVec3(0.0f, 0.0f, 0.0f);
}




