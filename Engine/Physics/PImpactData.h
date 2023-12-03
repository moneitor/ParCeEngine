#pragma once

#include "./PRBDBody.h"

struct pImpactData
{

    pImpactData() = default;
    ~pImpactData() = default;

    pRBDBody *a;
    pRBDBody *b;
    
    pVec3 startWorldSpace;
    pVec3 endWorldSpace;

    pVec3 collisionPosition;
    pVec3 collisionNormal;

    float collisionDepth;

    void ResolvePenetration();
    void ResolveCollision();
};