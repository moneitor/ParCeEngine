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

    float elasticity = a->Elasticity() * b->Elasticity();

    float invMassA = a->InvMass();
    float invMassB = b->InvMass();

    pMat3 invInertiaA = a->GetInertiaTensorWorldSpace(); // matrix is already inverted
    pMat3 invInertiaB = b->GetInertiaTensorWorldSpace();// matrix is already inverted

    pVec3 n = collisionNormal;

    pVec3 ra = endWorldSpace - a->Pos();
    pVec3 rb = startWorldSpace - b->Pos();

    pVec3 angularJa = Cross(invInertiaA * Cross(ra, n), ra);
    pVec3 angularJb = Cross(invInertiaB * Cross(rb, n), rb);
    float angularFactor = Dot((angularJa + angularJb), n);

    pVec3 linearVa = a->Vel();
    pVec3 linearVb = b->Vel();
    pVec3 angularVa = Cross(a->AngularVelocity(), ra);
    pVec3 angularVb = Cross(b->AngularVelocity(), rb);
    
    pVec3 va = linearVa + angularVa;
    pVec3 vb = linearVb + angularVb;

    pVec3 relV = va - vb;

    float impulseJ = -(1.0f + elasticity) * Dot(relV, n) / (invMassA + invMassB + angularFactor);
    pVec3 J = n.Scale(impulseJ);

    pVec3 angJ = Cross(ra, J);


    a->ApplyImpulse(J);
    a->ApplyAngularImpulse(angJ);
    b->ApplyImpulse(J * -1);
    b->ApplyAngularImpulse(angJ * -1);
    
}
