#include "PCollisionDetect.h"

bool pCollisionDetection::RayToSphere(const pVec3 &rayStart, const pVec3 &rayDir, const pVec3 &sphereCenter, float sphereRadius, float &time1, float &time2)
{
    pVec3 m = sphereCenter - rayStart;
    float a = Dot(rayDir, rayDir);
    float b = Dot(m, rayDir);
    float c = Dot(m, m) - sphereRadius * sphereRadius;

    float delta = b * b - a * c;

    float invA = 1.0f / a;

    if(delta < 0)
    {
        return false;
    }

    const float deltaRoot = sqrtf(delta);
    time1 = invA * (b - deltaRoot);
    time2 = invA * (b + deltaRoot);

    return true;
}


bool pCollisionDetection::IsCollidingSphereSphere(pRBDBody *a, pRBDBody *b, pImpactData &impactData, float dt)
{
    float aRadius = static_cast<pRBDSphere*>(a->GetShape())->GetRadius();
    float bRadius = static_cast<pRBDSphere*>(b->GetShape())->GetRadius();

    float totalRadius = (aRadius + bRadius);

    pVec3 aPos = a->Pos();
    pVec3 bPos = b->Pos();
    pVec3 collisionNormal = bPos - aPos;
    
    float distSquared = (collisionNormal).MagnitudeSq();
    
    float t0, t1;
    
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
    else if (!RayToSphere(a->Pos(), collisionNormal.Normalize(), b->Pos(), aRadius + bRadius, t0, t1))
    {
        return false;
    }

    t0 *= dt;
    t1 *= dt;

    // If the collision is only in the past, then there's not future collision this frame
	if ( t1 < 0.0f ) {
		return false;
	}

	// Get the earliest positive time of impact
	impactData.timeOfImpact = ( t0 < 0.0f ) ? 0.0f : t0;

	// If the earliest collision is too far in the future, then there's no collision this frame
	if ( impactData.timeOfImpact > dt ) {
		return false;
	}
    
    Utility::AddMessage(std::to_string(t0));
    Utility::AddMessage(std::to_string(t1));
    Utility::AddMessage("\n");

    // Utility::AddMessage("NOT Colliding");
    return false;
}


bool pCollisionDetection::IsColliding(pRBDBody *a, pRBDBody *b, pImpactData &impactData, float dt)
{
    bool aIsSphere = a->GetShape()->GetShapeType() == SPHERE;
    bool bIsSphere = b->GetShape()->GetShapeType() == SPHERE;

    if(aIsSphere && bIsSphere)
    {
        return IsCollidingSphereSphere(a, b, impactData, dt);
    }

    return false;
}
