#pragma once

#include "./PRBDBody.h"
#include "./PImpactData.h"
#include "./Primitives/PRay.h"

class pCollisionDetection
{
public:
    static bool RayToSphere(const pVec3 &rayStart, const pVec3 &rayDir, const pVec3 &sphereCenter, float sphereRadius, float &time1, float &time2);

    static bool IsColliding(pRBDBody *a, pRBDBody *b, pImpactData &impactData, float dt);
    static bool IsCollidingSphereSphere(pRBDBody *a, pRBDBody *b, pImpactData &impactData, float dt);
    static bool IsCollidingConvexConvex(pRBDBody *a, pRBDBody *b, pImpactData &impactData, float dt);
    static bool IsCollidingSphereConvex(pRBDBody *a, pRBDBody *b, pImpactData &impactData, float dt);

private:
    pRBDBody *a;
    pRBDBody *b;

    pImpactData *impactData;
};