#include "PCollisionDetect.h"

bool pCollisionDetection::IsColliding(pRBDBody *a, pRBDBody *b, pImpactData &impactData)
{
    bool aIsSphere = a->GetShape()->GetShapeType() == SPHERE;
    bool bIsSphere = b->GetShape()->GetShapeType() == SPHERE;

    if(aIsSphere && bIsSphere)
    {
        return IsCollidingSphereSphere(a, b);
    }

    return false;
}

bool pCollisionDetection::IsCollidingSphereSphere(pRBDBody *a, pRBDBody *b)
{
    float aRadius = static_cast<pRBDSphere*>(a->GetShape())->GetRadius();
    float bRadius = static_cast<pRBDSphere*>(b->GetShape())->GetRadius();

    float totalRadius = (aRadius + bRadius);

    pVec3 aPos = a->Pos();
    pVec3 bPos = b->Pos();

    float distSquared = (aPos - bPos).MagnitudeSq();

    if(distSquared < (totalRadius * totalRadius))
    {
        a->SetIsColliding(true);
        Utility::AddMessage("Colliding");
        return true;
    }
    a->SetIsColliding(false);
    Utility::AddMessage("NOT Colliding");
    return false;
}
