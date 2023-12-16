#include "PImpactData.h"

void pImpactData::ResolvePenetration()
{
    float da = collisionDepth / (a->InvMass() + b->InvMass()) * a->InvMass();
    float db = collisionDepth / (a->InvMass() + b->InvMass()) * b->InvMass();

    pVec3 aPos = a->Pos();
    if(a->IsActive() == true)
    {
        a->SetPosition(aPos - (collisionNormal * da));
    }
    pVec3 bPos = b->Pos();
    if(b->IsActive() == true)
    {
        b->SetPosition(bPos + (collisionNormal * db));
    }
}

void pImpactData::ResolveCollision()
{
    pVec3 ptOnA = startWorldSpace;
    pVec3 ptOnB = endWorldSpace;

    float elasticity = a->Elasticity() * b->Elasticity();

    float invMassA = a->InvMass();
    float invMassB = b->InvMass();

    pMat3 invInertiaA = a->GetInertiaTensorWorldSpace(); // matrix is already inverted
    pMat3 invInertiaB = b->GetInertiaTensorWorldSpace(); // matrix is already inverted

    pVec3 n = collisionNormal;

    pVec3 ra = ptOnA - a->Pos();
    pVec3 rb = ptOnB - b->Pos();

    pVec3 angularJa = Cross(invInertiaA * Cross(ra, n), ra);
    pVec3 angularJb = Cross(invInertiaB * Cross(rb, n), rb);
    float angularFactor = Dot((angularJa + angularJb), n);
  
    pVec3 velA = a->Vel() + Cross(a->AngularVelocity(), ra);
    pVec3 velB = b->Vel() + Cross(b->AngularVelocity(), rb);

    pVec3 vab = velA - velB;    

    float impulseJ = ((1.0f + elasticity) * Dot(vab, n)) / (invMassA + invMassB + angularFactor);
    pVec3 JN = n.Scale(impulseJ);

    a->ApplyImpulse(ptOnA, JN * -1);
    b->ApplyImpulse(ptOnB, JN );


    // Solving impulse based on FRICTION ======================
    float friction = a->Friction() * b->Friction();

    pVec3 velNorm = n * Dot(n, vab);

    pVec3 velTang =  vab - velNorm;

    pVec3 relativeVelTang = velTang.Normalize(); 


    pVec3 inertiaA = Cross( invInertiaA * Cross(ra, relativeVelTang),  ra);
    pVec3 inertiaB = Cross( invInertiaB * Cross(rb, relativeVelTang),  rb);
    float invInertia = Dot((inertiaA + inertiaB), relativeVelTang);

    float reducedMass = 1.0f / (invMassA + invMassB + invInertia);
    pVec3 JF = velTang * reducedMass * friction ;

    a->ApplyImpulse(ptOnA, JF * -1);
    b->ApplyImpulse(ptOnB, JF );


    ResolvePenetration();

}
