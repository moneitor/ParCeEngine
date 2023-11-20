#include "PRBDBody.h"

pRBDBody::pRBDBody(pRBDShape *shape, float mass_)
:rbdShape{shape},
position{pVec3(0.0f, 0.0f, 0.0f)},
velocity{pVec3(0.0f)},
acceleration{pVec3(0.0f)},
netForce{pVec3(0.0f)},
orientation{pQuat()},
angVelocity{pVec3(0.0f)},
angAcceleration{pVec3(0.0f)},
netTorque{pVec3(0.0f)},
// transform{pMat4()},
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

pRBDBody::pRBDBody(pRBDShape *shape, const pVec3 &pos, const pQuat &orient, float mass_)
:rbdShape{shape},
position{pos},
velocity{pVec3(0.0f)},
acceleration{pVec3(0.0f)},
netForce{pVec3(0.0f)},
orientation{pQuat()},
angVelocity{pVec3(0.0f)},
angAcceleration{pVec3(0.0f)},
netTorque{pVec3(0.0f)},
// transform{pMat4()},
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

void pRBDBody::SetOrientation(const glm::quat orient)
{
    this->orientation = orient;
}

pQuat pRBDBody::Orient()
{
    return orientation;
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

pVec3 pRBDBody::AngularVelocity()
{
    return this->angVelocity;
}

pVec3 pRBDBody::AngularAcceleration()
{
    return this->angAcceleration;
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

void pRBDBody::AddTorque(const pVec3 &torque)
{
    this->netTorque += torque;
}

void pRBDBody::CleanForces()
{
    this->netForce = pVec3(0.0f);
}

void pRBDBody::CleanTorques()
{
    this->netTorque = pVec3(0.0f);
}

void pRBDBody::SetActive(bool value)
{
    this->active = value;
}


pVec3 pRBDBody::WorldToLocal(pVec3 &vec) 
{
    pVec3 tempVec = vec;
    pVec3 temp = tempVec - GetCenterOfMassWorldSpace();
    pQuat invOrient = orientation.Invert();
    pVec3 localSpace = RotateVector(invOrient, temp);

    return localSpace;
}

pVec3 pRBDBody::LocalToWorld(pVec3 &vec) 
{
    pVec3 worldSpace = GetCenterOfMassWorldSpace() + RotateVector(orientation, vec);
    return worldSpace;

}

pVec3 pRBDBody::GetCenterOfMassWorldSpace() 
{
    pVec3 centerOfMass = rbdShape->GetCenterOfMass();

    const pVec3 pos = position + RotateVector(orientation, centerOfMass);
    return pos;
}

pVec3 pRBDBody::GetCenterOfMassLocalSpace() 
{
    const pVec3 com = rbdShape->GetCenterOfMass();
    return com;
}

pMat3 pRBDBody::GetInertiaTensorWorldSpace()
{
    pMat3 I = rbdShape->GetInertiaTensor() * invMass;
    pMat3 orient = orientation.ToMatrix();
    I = orient * I * orient.Transpose();
    return I;
}

pMat3 pRBDBody::GetInertiaTensorLocalSpace()
{
    return rbdShape->GetInertiaTensor() * invMass;    
}

void pRBDBody::IntegrateLinear(float dt)
{
    if(active)
    {
        this->acceleration = netForce * invMass;
        this->velocity += acceleration * dt;
        this->position += Vel() * dt;
    }

    CleanForces();
}

void pRBDBody::IntegrateAngular(float dt)
{
    if(active)
    {
        
        pMat3 I = GetInertiaTensorWorldSpace(); // This matrix is already inverted

        angAcceleration = netTorque * I;

        angVelocity += angAcceleration * dt;

        float maxAngSpeed = 0.005f;
        if (angVelocity.MagnitudeSq() > maxAngSpeed * maxAngSpeed)
        {
            pVec3 newAngVelocity = angVelocity.Normalize();
            angVelocity = newAngVelocity * maxAngSpeed;
        }

        pQuat dq = pQuat(angVelocity.Magnitude(), angVelocity);


        orientation = dq * orientation;
        orientation.Normalize();
        


    }

    CleanTorques();
}
