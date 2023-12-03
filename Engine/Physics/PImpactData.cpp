#include "PImpactData.h"

void pImpactData::ResolvePenetration()
{
    float da = collisionDepth / (a->InvMass() + b->InvMass()) * a->InvMass();
    float db = collisionDepth / (a->InvMass() + b->InvMass()) * b->InvMass();

    pVec3 aPos = a->Pos();
    a->SetPosition(aPos - (collisionNormal * da));

    pVec3 bPos = b->Pos();
    b->SetPosition(bPos + (collisionNormal * da));
    
}

void pImpactData::ResolveCollision()
{
    ResolvePenetration();

    float elasticity = std::min(a->Elasticity(), b->Elasticity());

    pVec3 relativeVelocity = a->Vel() - b->Vel();

    float velAlongColNormal = Dot(relativeVelocity, collisionNormal);

    pVec3 impulseDirection = collisionNormal;    

    float impulseMagnitude = -(1 + elasticity) * velAlongColNormal / (a->InvMass() + b->InvMass());

    pVec3 J = impulseDirection.Scale(impulseMagnitude);


    a->ApplyImpulse(J);
    b->ApplyImpulse(J * -1);
}
