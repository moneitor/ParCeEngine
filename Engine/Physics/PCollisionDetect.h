#pragma once

#include "./PRBDBody.h"
#include "./PImpactData.h"

class pCollisionDetection
{
public:
    static bool IsColliding(pRBDBody *a, pRBDBody *b, pImpactData &impactData);
    static bool IsCollidingSphereSphere(pRBDBody *a, pRBDBody *b);
    static bool IsCollidingConvexConvex(pRBDBody *a, pRBDBody *b);
    static bool IsCollidingSphereConvex(pRBDBody *a, pRBDBody *b);

private:
    pRBDBody *a;
    pRBDBody *b;

    pImpactData *impactData;
};