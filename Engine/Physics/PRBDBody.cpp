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
active{true},
isColliding{false},
friction{0.9f},
transform{pMat4()},
angularDamping{1.0f},
linearDamping{0.0f},
isSleeping{false}
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
active{true},
orig_position{pos},
orig_orientation{orient},
isColliding{false},
friction{0.9f},
transform{pMat4()},
angularDamping{1.0f},
linearDamping{0.0f},
isSleeping{false}
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

float pRBDBody::Friction()
{
    return friction;
}

void pRBDBody::SetFriction(float _friction)
{
    this->friction = _friction;
}

float pRBDBody::Mass()
{
    return this->mass;
}

void pRBDBody::SetMass(float value)
{
    this->mass = value;
}

float pRBDBody::InvMass()
{
    return this->invMass;
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

bool pRBDBody::IsActive() const
{
    if(compareDouble(invMass, 0.0f))
    {
        return false;
    }
    return active;
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
    // Utility::AddMessage(I.ToString());
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
    if(IsActive() == true)
    {
        this->acceleration = netForce * invMass;
        this->velocity += acceleration * dt;
        // this->velocity *= pow(linearDamping, dt);
        this->position += Vel() * dt;
    }

    CleanForces();
}


void pRBDBody::IntegrateAngular(float dt)
{
    if(IsActive() == true)
    {        
        pVec3 positionCM = GetCenterOfMassWorldSpace();
        pVec3 cmToPos = Pos() - positionCM;

        angAcceleration = GetInertiaTensorWorldSpace() * netTorque;

        angVelocity = angVelocity + angAcceleration * dt;

        pMat3 inertiaTensor = GetInertiaTensorWorldSpace();
        pVec3 alpha = Inverse(inertiaTensor) * ( Cross(angVelocity,  inertiaTensor * angVelocity) );
        this->angVelocity = angVelocity + alpha * dt;

        this->angVelocity = angVelocity * pow(angularDamping, dt);

        pVec3 dAngle = angVelocity * dt;
        
        pQuat dq = pQuat(dAngle.Magnitude(), dAngle);
        this->orientation = dq * orientation;
        this->orientation = orientation.Normalize();

        this->position = positionCM + RotateVector(orientation, cmToPos);

    }

    CleanTorques();
}

void pRBDBody::IntegrateBody(float dt, float elapsedTime)
{
    if(IsActive() == true)
    {
        if(!IsSleeping())
        {
            this->IntegrateLinear(dt);
            this->IntegrateAngular(dt);
        }

        if(this->velocity.Magnitude() < 0.1 && this->angVelocity.Magnitude() < 10)
        {
            if(elapsedTime > 20)
            {
                SetIsSleeping(true);
            }
        }

        GetShape()->UpdateVertices(Orient(), Pos());
    }
}

bool pRBDBody::IsColliding() const
{
    return isColliding;
}

void pRBDBody::SetIsSleeping(bool val)
{
    this->isSleeping = val;
    SetActive(false);
}

bool pRBDBody::IsSleeping() const
{
    return this->isSleeping;
}

void pRBDBody::ApplyImpulseLinear(const pVec3 &impulse)
{
    if(IsActive() != true)
    {
        return;
    }

    pVec3 finalImpulse = impulse.Scale(invMass);

    velocity = velocity + finalImpulse;
}

void pRBDBody::ApplyImpulseAngular(const pVec3 &impulse)
{
    if(IsActive() != true)
    {
        return;
    }

    pMat3 I = GetInertiaTensorWorldSpace();

    angVelocity = angVelocity + (I * impulse);

    float maxAngSpeed = 130.0f;
    if (angVelocity.MagnitudeSq() > maxAngSpeed * maxAngSpeed)
    {
        pVec3 newAngVelocity = angVelocity.Normalize();
        angVelocity = newAngVelocity * maxAngSpeed;
    }

    // angVelocity *= pow(angularDamping, 0.016f);
}

void pRBDBody::ApplyImpulse(const pVec3 &impulsePoint, const pVec3 & impulse)
{
    if(IsActive() != true)
    {
        return;
    }

    // linear impulse
    ApplyImpulseLinear(impulse);

    // angular impulse
    pVec3 re = impulsePoint - Pos();
    pVec3 dl = Cross(re, impulse);

    ApplyImpulseAngular(dl);

}

void pRBDBody::SetAngularDamping(float angularDamping)
{
    this->angularDamping = angularDamping;
}

void pRBDBody::setLinearDamping(float linearDamping)
{
    this->linearDamping = linearDamping;
}

pMat4 pRBDBody::GetTransform()
{
    float _e11, _e12, _e13, _e14,
          _e21, _e22, _e23, _e24, 
          _e31, _e32, _e33, _e34;

    _e11 = 1.0f - 2.0f * orientation.GetY() * orientation.GetY() - 2.0f * orientation.GetZ() * orientation.GetZ();
    _e12 = 2.0f * orientation.GetX() * orientation.GetY() + 2.0f * orientation.GetZ() * orientation.GetW();
    _e13 = 2.0f * orientation.GetX() * orientation.GetZ() - 2.0f * orientation.GetY() * orientation.GetW();
    _e14 = position.GetX();

    _e21 = 2.0f * orientation.GetX() * orientation.GetY() - 2.0f * orientation.GetZ() * orientation.GetW();
    _e22 = 1.0f - 2.0f * orientation.GetX() * orientation.GetX() - 2.0f * orientation.GetZ() * orientation.GetZ();
    _e23 = 2.0f * orientation.GetY() * orientation.GetZ() + 2.0f * orientation.GetX() * orientation.GetW();
    _e24 = position.GetY();

    _e31 = 2.0f * orientation.GetX() * orientation.GetZ() + 2.0f * orientation.GetY() * orientation.GetW();
    _e32 = 2.0f * orientation.GetY() * orientation.GetZ() - 2.0f * orientation.GetX() * orientation.GetW();
    _e33 = 1.0f - 2.0f * orientation.GetX() * orientation.GetX() - 2.0f * orientation.GetY() * orientation.GetY();
    _e34 = position.GetZ();

    return pMat4(_e11, _e12, _e13, _e14,
                 _e21, _e22, _e23, _e24, 
                 _e31, _e32, _e33, _e34,
                 0.0f, 0.0f, 0.0f, 1.0f);
}

void pRBDBody::SetIsColliding(bool val)
{
    isColliding = val;
}
