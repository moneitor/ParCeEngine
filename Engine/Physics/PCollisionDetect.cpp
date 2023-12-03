#include "PCollisionDetect.h"

bool pCollisionDetection::IsColliding(pRBDBody *a, pRBDBody *b, pImpactData &impactData)
{
    bool aIsSphere = a->GetShape()->GetShapeType() == SPHERE;
    bool bIsSphere = b->GetShape()->GetShapeType() == SPHERE;

    if(aIsSphere && bIsSphere)
    {
        return IsCollidingSphereSphere(a, b, impactData);
    }

    return false;
}

bool pCollisionDetection::IsCollidingSphereSphere(pRBDBody *a, pRBDBody *b, pImpactData &impactData)
{
    float aRadius = static_cast<pRBDSphere*>(a->GetShape())->GetRadius();
    float bRadius = static_cast<pRBDSphere*>(b->GetShape())->GetRadius();

    float totalRadius = (aRadius + bRadius);

    pVec3 aPos = a->Pos();
    pVec3 bPos = b->Pos();
    pVec3 collisionNormal = bPos - aPos;
    
    float distSquared = (collisionNormal).MagnitudeSq();
    
    if(distSquared < (totalRadius * totalRadius))
    {
        // Utility::AddMessage("Colliding");

        impactData.a = a;
        impactData.b = b;       
        
        impactData.collisionNormal = collisionNormal.Normalize();

        impactData.startWorldSpace = bPos - impactData.collisionNormal * bRadius;
        impactData.endWorldSpace =   aPos + impactData.collisionNormal * aRadius;

        impactData.collisionDepth = (impactData.startWorldSpace - impactData.endWorldSpace).Magnitude();
        return true;
    }

    // Utility::AddMessage("NOT Colliding");
    return false;
}
