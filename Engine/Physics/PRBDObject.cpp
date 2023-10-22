#include "PRBDObject.h"

pRBDObject::pRBDObject()
    :elasticity{1},
    mass{1},
    position{pVec3(0.0f, 0.0f, 0.0f)}

{
}

pRBDObject::pRBDObject(const pVec3 & pos)
    :position{pos}
{
}

pRBDObject::pRBDObject(assModel * model)
    :object{model}
{
}

pRBDObject::pRBDObject(assModel * model, const pVec3 &pos)
    :position{pos}, 
    object{model}
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
    return this->velocity;
}

void pRBDObject::SetVelocity(const pVec3 & vel)
{
    this->velocity = vel;
}

void pRBDObject::SetVelocity(float x, float y, float z)
{
    this->velocity = pVec3(x, y, z);
}

void pRBDObject::SetElasticity(float elasticity_)
{
    this->elasticity = elasticity_;
}

float pRBDObject::Elasticity()
{
    return this->elasticity;
}



